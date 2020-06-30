//
// Created by sv.yarakaev on 25.06.2020.
//

#ifndef WINDOWAPP_UTILS_H
#define WINDOWAPP_UTILS_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char *cmd);

const  std::string text_up_exp = R""""(
set ssh_port                 [lindex $argv 0]
set sftp_server              [lindex $argv 1]
set sftp_user                [lindex $argv 2]
set sftp_pass                [lindex $argv 3]
set target_directory         [lindex $argv 4]
set source_directory         [lindex $argv 5]
set file_name                [lindex $argv 6]
set rename_file              [lindex $argv 7]
set sftp_prompt "sftp>?"
set timeout 300

if { $rename_file eq "" } {
  set rename_file N
}

proc connect { sftp_pass } {
  variable sftp_prompt
  variable sftp_server
  expect -re "Connecting to.*"                     { exp_continue } \
         -re "Are you sure you want to continue.*" { exp_send "YES\r"; exp_continue } \
         -re "(Password|password).*:.*"            { exp_send "$sftp_pass\r"; exp_continue } \
         -re $sftp_prompt                          { return 0 } \
         eof                                       { puts "***Error connecting to($sftp_server)."; return 1 }
         timeout                                   { puts "***Error connecting to($sftp_server)."; return 1 }
  }

proc abort { msg } {
  puts "$msg";
  exp_send "quit\r";
  exit 1;
  }


spawn sftp -oPort=$ssh_port $sftp_user@$sftp_server
set connect_results [connect $sftp_pass]

if { $connect_results == 0 } {
  # Change to target directory on target server.
  exp_send "cd $target_directory\r"
    expect "No such file or directory" { abort "\n**Error changing to directory($target_directory) on target server." } \
           "Failure"                   { abort "\n**Error changing to directory($target_directory) on target server." } \
           -re $sftp_prompt            {} \
           timeout { abort "\n**Error changing to directory($target_directory) on target server." }

  # Change local directory.
  exp_send "lcd $source_directory\r"
    expect "No such file or directory" { abort "\n**Error changing to directory($source_directory) on local machine." } \
           "Failure"                   { abort "\n**Error changing to directory($source_directory) on local machine." } \
           -re $sftp_prompt            {} \
           timeout { abort "\n**Error changing to directory($source_directory) on local machine." }

  # If rename_file = "Y" transfer file with '.xferring' as extension.
  if { $rename_file == "Y" } {
    set file_name_to_xfer $file_name
    append file_name_to_xfer .xferring
  } else {
    set file_name_to_xfer $file_name
  }

  # Put file to target host.
  set timeout 1800
  exp_send "put $file_name $file_name_to_xfer\r"
    expect "not found."                { abort "\n***Error transfering file($file_name) to: $sftp_server)." } \
           "No such file or directory" { abort "\n***Error transfering file($file_name) to: $sftp_server)." } \
           "Failure"                   { abort "\n***Error transfering file($file_name) to: $sftp_server)." } \
           -re $sftp_prompt            {} \
           timeout { abort "\n***Error transfering file($file_name) to: $sftp_server)." }

  # If rename_file = "Y" remove extension '.xferring' from file name after successful transfer.
  if { $rename_file == "Y" } {
    exp_send "rename $file_name_to_xfer $file_name\r"
      expect "No such file or directory" { abort "\n***Error renaming file($file_name_to_xfer) to($file_name) on $sftp_server)." } \
             "Failure"                   { abort "\n***Error renaming file($file_name_to_xfer) to($file_name) on $sftp_server)." } \
             -re $sftp_prompt            {} \
             timeout { abort "\n***Error renaming file($file_name_to_xfer) to($file_name) on $sftp_server)." }
  }

  # QUIT!!
  exp_send "quit\r"
  # Successful SFTP session so exit with zero status
  exit 0
}
# Error connecting to SFTP server so exit with non-zero status
exit 1


)"""";

const std::string text_up_exp_m = R""""(
    #!/usr/bin/expect --
# Script: run_sftp_script.tcl
# Description: Utility to run a SFTP script
# usage: run_sftp.tcl target_server_port target_server user pass sftp_script_name

# Set named parameters
set ssh_port                 [lindex $argv 0]
set sftp_server              [lindex $argv 1]
set sftp_user                [lindex $argv 2]
set sftp_pass                [lindex $argv 3]
set sftp_script_name         [lindex $argv 4]
set sftp_prompt "sftp>?"
set timeout 30

# Procedure to connect to SFTP server
proc connect { sftp_pass } {
  variable sftp_prompt
  variable sftp_server
  expect -re "debug1:.*"                           { exp_continue } \
         -re "Connecting to.*"                     { exp_continue } \
         -re "Are you sure you want to continue.*" { exp_send "YES\r"; exp_continue } \
         "Password:"                               { exp_send "$sftp_pass\r"; exp_continue } \
         -re $sftp_prompt                          { return 0 } \
         -re .                                     { exp_continue  }
         eof                                       { puts "***Error connecting to($sftp_server)."; return 1 }
         timeout                                   { puts "***Error connecting to($sftp_server)."; return 1 }
  }

# Procedure to run SFTP commands from file
proc send_sftp_commands { sftp_script_name } {
  variable sftp_prompt
  #  Slurp up the sftp commands from file
  set fp [open "$sftp_script_name" r]
  set sftp_cmds [read $fp]
  close $fp

  #  Process sftp commands
  set sftp_command_list [split $sftp_cmds "\n"]

  foreach sftp_command $sftp_command_list {
    set comment [string index $sftp_command 0]
    if { $comment == "#" || $comment == "" } {
      continue
    }
    exp_send "$sftp_command\r"
      expect -re "Uploading.*"           { exp_continue } \
             "Failure"                   { abort "\n**Error running command($sftp_command)." } \
             -re $sftp_prompt            {} \
             timeout { abort "\n**Error running command($sftp_command)." }
  }
  return 0
}

# Procedure to send meesage denoting error, then quit SFTP, then exit with status denoting error.
proc abort { msg } {
  puts "$msg"
  exp_send "quit\r";
  exit 1;
  }

# Connect to the SFTP server and run sftp commands
spawn sftp -v -oPort=$ssh_port $sftp_user@$sftp_server
set connect_results [connect $sftp_pass]

# If successful connection, continue, else exit denoting error occured.
if { $connect_results == 0 } {
  puts "Successful connection/login to target host($sftp_server)."
  set sftp_results [send_sftp_commands $sftp_script_name]
  # If successful connection, continue, else exit denoting error occured.
  if { $sftp_results == 0 } {
    puts "Successful sftp session to target host($sftp_server)."
  # Successful SFTP session so exit with zero status
  exit 0
  }
}
# Error connecting to SFTP server so exit with non-zero status
puts "***Error running sftp script($sftp_script_name), for target host($sftp_server)."
exit 1

)"""";

const std::string install_eqv = "";
const std::string uninstall_eqv = "";





#endif //WINDOWAPP_UTILS_H
