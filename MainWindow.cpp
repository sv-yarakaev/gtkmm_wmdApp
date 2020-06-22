//
// Created by sv.yarakaev on 09.06.2020.
//

#include "MainWindow.h"
MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
        : Gtk::Window(cobject),
          m_refGlade(refGlade),
          //m_pComboBoxIPAddr(true),
          m_pButton(nullptr),
          //m_pComboBoxIPAddr(nullptr),
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


    //m_pComboBoxIPAddr = new GtkComboBoxText (true);
    m_refGlade->get_widget("comboIPAddr", m_pComboBoxIPAddr);
    //m_pComboBoxIPAddr->get_has_entry();

    m_pComboBoxIPAddr->signal_changed().connect(sigc::mem_fun(*this,
                                                              &MainWindow::on_comboIP_changed) );

    m_refGlade->get_widget("viewLog", m_pViewLog);
    m_refGlade->get_widget("btnLoad", m_pbtnLoad);
    //m_refGlade->get_widget("editIPAddr", m_pEntryIPAddress);
    m_pEntryIPAddress = m_pComboBoxIPAddr->get_entry();

    m_pbtnLoad->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_Load));
    m_pComboBoxIPAddr->set_active(0);

    m_pEntryIPAddress->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_entry_changed));

    m_pEntryIPAddress->add_events(Gdk::FOCUS_CHANGE_MASK);
    m_pEntryIPAddress->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_entry_activate));
    m_ConnectionFocusOut = m_pEntryIPAddress->signal_focus_out_event().
            connect(sigc::mem_fun(*this, &MainWindow::on_entry_focus_out_event) );

    m_refTextBuffer1 = Gtk::TextBuffer::create();
    iter = m_refTextBuffer1->get_iter_at_offset(0);

    iter = m_refTextBuffer1->insert (iter, "Create and running interface for load\n");
    //iter = m_refTextBuffer1->get_iter_at_offset(0);
    m_pViewLog->set_buffer(m_refTextBuffer1);

    //m_pComboBoxIPAddr->property_has_frame() = false;
    //TODO Remove its appneds
//    m_pComboBoxIPAddr->append("10.243.12.178"); m_pComboBoxIPAddr->append("10.243.12.179");
//    m_pComboBoxIPAddr->append("10.243.12.180"); m_pComboBoxIPAddr->append("10.243.12.181");
//    m_pComboBoxIPAddr->append("10.243.12.182"); m_pComboBoxIPAddr->append("10.243.12.183");
    m_pComboBoxIPAddr->set_active(0);
    m_pComboBoxIPAddr->set_sensitive(true);
    m_pEntryIPAddress->set_sensitive(true);


    show_all();

}


MainWindow::~MainWindow()
{
    m_ConnectionHasFocusChanged.disconnect();
    delete m_addIPWindow;
}

void MainWindow::on_button_quit()

{
    iter = m_refTextBuffer1 ->insert(iter,"Bye!\n");
    m_pViewLog->set_buffer(m_refTextBuffer1);
    std::cout << "Bye!" <<std::endl;
    hide(); //hide() will cause Gtk::Application::run() to end.
}

void MainWindow::on_button_Load() {

    m_pComboBoxIPAddr->get_active_text();
    std::string out = "IP address button load is clicked " + m_pComboBoxIPAddr->get_active_text() + "\n";
    writeToLog(out);

}

void MainWindow::writeToLog(std::string text) {
    iter = m_refTextBuffer1 ->insert(iter,text);
    m_pViewLog->set_buffer(m_refTextBuffer1);

}

void MainWindow::on_comboIP_changed() {
    Glib::ustring text = m_pComboBoxIPAddr->get_active_text();

    if(!(text.empty())) {
        std::cout << "Combo changed: " << text << std::endl;
        writeToLog(" Combo changes " + text + "\n");
    }
    std::cout << "on_combo_changed(): Row=" << m_pComboBoxIPAddr->get_active_row_number()
              << ", Text=" << m_pComboBoxIPAddr->get_active_text() << std::endl;

}

void MainWindow::on_entry_changed() {
    std::cout << "Calling from on_entry_changed()\n";
    std::cout << "on_combo_changed(): Row=" << m_pComboBoxIPAddr->get_active_row_number()
              << ", Text=" << m_pComboBoxIPAddr->get_active_text() << std::endl;

}
void MainWindow::on_entryIP_has_focus_changed() {
    std::cout <<"Calling from Entry IP box \n";
    auto entry = m_pEntryIPAddress;
    const bool entry_has_focus = entry->has_focus();

    m_entry_had_focus = entry_has_focus;

}

void MainWindow::on_entry_activate() {
    entry = m_pComboBoxIPAddr->get_entry();
}

bool MainWindow::on_entry_focus_out_event(GdkEventFocus* /* event */)
{
    //Gtk::Entry* entry = m_pComboBoxIPAddr->get_entry();
    if (entry)
    {
        std::cout << "on_entry_focus_out_event(): Строка модели=" << m_pComboBoxIPAddr->get_active_row_number()
                  << ", Идентификатор=" << entry->get_text() << std::endl;
        return true;
    }
    return false;
}

void MainWindow::on_entry_has_focus_changed() {
    //Gtk::Entry* entry = m_pComboBoxIPAddr->get_entry();
    if (entry)
    {
        const bool entry_has_focus = entry->has_focus();
        if (m_entry_had_focus && !entry_has_focus)
        {
            // entry->has_focus() has changed from true to false; entry has lost focus.
            std::cout << "on_entry_has_focus_changed() to not focused: Row="
                      << m_pComboBoxIPAddr->get_active_row_number() << ", ID=" << entry->get_text() << std::endl;
        }
        m_entry_had_focus = entry_has_focus;
    }
}