//
// Created by sv.yarakaev on 09.06.2020.
//

#ifndef WINDOWAPP_MAINWINDOW_H
#define WINDOWAPP_MAINWINDOW_H

#include <gtkmm.h>


class MainWindow : public Gtk::Window {
public:
    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);
    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade, bool is_glad);

    virtual ~MainWindow();
protected:
    void on_button_quit();

    Glib::RefPtr<Gtk::Builder> m_refGlade;
    Gtk::Button *m_pButton;
};


#endif //WINDOWAPP_MAINWINDOW_H
