//
// Created by sv.yarakaev on 09.06.2020.
//

#ifndef WINDOWAPP_MAINWINDOW_H
#define WINDOWAPP_MAINWINDOW_H

#include <iostream>
#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/application.h>

#include "utils.h"




class MainWindow : public Gtk::Window {
public:
    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);


    virtual ~MainWindow();
protected:
    void on_button_quit();
    void on_button_Load();
    void on_comboIP_changed();
    void on_entry_changed();
    void on_entryIP_has_focus_changed();
    void on_entry_activate();
    bool on_entry_focus_out_event(GdkEventFocus* );
    void on_entry_has_focus_changed();
    sigc::connection m_ConnectionHasFocusChanged;


    Glib::RefPtr<Gtk::Builder> m_refGlade;
    Gtk::Dialog *m_addIPWindow;
    Gtk::Button *m_pButton;
    Gtk::Button *m_pModalButton;
    Gtk::ComboBoxText *m_pComboBoxIPAddr;
    Gtk::TextView *m_pViewLog;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1, m_refTextBuffer2;
    Gtk::TextBuffer::iterator iter; //find my seek
    sigc::connection m_ConnectionFocusOut;
    Gtk::Button *m_pbtnLoad;
    Gtk::Entry *m_pEntryIPAddress;
    Gtk::Entry *entry;
    //sigc::connection m_ConnectionHasFocusChanged; //for comboboxtext changes
    bool m_entry_had_focus {false};

private:
    void writeToLog(std::string);
    void init();
};


#endif //WINDOWAPP_MAINWINDOW_H
