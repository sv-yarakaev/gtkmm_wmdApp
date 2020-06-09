//
// Created by sv.yarakaev on 09.06.2020.
//

#include "MainWindow.h"
MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
        : Gtk::Window(cobject),
          m_refGlade(refGlade),
          m_pButton(nullptr),
          m_pComboBoxIPAddr(nullptr),
          m_pViewLog(nullptr),
          m_pbtnLoad(nullptr),
          iter(nullptr)
{
    set_title("Proto for loader MPC-L");
    //Get the Glade-instantiated Button, and connect a signal handler:
    m_refGlade->get_widget("btnQuit", m_pButton);
    if(m_pButton)
    {
        m_pButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::on_button_quit) );
    }
    m_refGlade->get_widget("comboIPAddr", m_pComboBoxIPAddr);
    m_refGlade->get_widget("viewLog", m_pViewLog);
    m_refGlade->get_widget("btnLoad", m_pbtnLoad);

    m_pbtnLoad->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_Load));

    m_refTextBuffer1 = Gtk::TextBuffer::create();
    iter = m_refTextBuffer1->get_iter_at_offset(0);

    iter = m_refTextBuffer1->insert (iter, "Create and running interface for load\n");
    //iter = m_refTextBuffer1->get_iter_at_offset(0);
    m_pViewLog->set_buffer(m_refTextBuffer1);

}


MainWindow::~MainWindow()
{
}

void MainWindow::on_button_quit()

{
    iter = m_refTextBuffer1 ->insert(iter,"Bye!\n");
    m_pViewLog->set_buffer(m_refTextBuffer1);
    hide(); //hide() will cause Gtk::Application::run() to end.
}

void MainWindow::on_button_Load() {
    iter = m_refTextBuffer1 ->insert(iter,"IP address button load click\n");
    m_pViewLog->set_buffer(m_refTextBuffer1);
}