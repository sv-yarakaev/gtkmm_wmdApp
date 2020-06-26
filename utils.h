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







#endif //WINDOWAPP_UTILS_H
