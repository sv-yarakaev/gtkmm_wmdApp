//
// Created by sv.yarakaev on 10.06.2020.
//

#ifndef WINDOWAPP_ADDIPMODAL_H
#define WINDOWAPP_ADDIPMODAL_H
#include <gtkmm.h>

class AddIPModal : public Gtk::Window  {
public:
    AddIPModal();
    virtual ~AddIPModal();

protected:
    void on_button_quit();

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        ModelColumns()
        { add(m_col_id); add(m_col_name); add(m_col_number); add(m_col_percentage);}

        Gtk::TreeModelColumn<unsigned int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<short> m_col_number;
        Gtk::TreeModelColumn<int> m_col_percentage;
    };

    ModelColumns m_Columns;

    //Дочерние виджеты:
    Gtk::Box m_VBox;

    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Quit;

};


#endif //WINDOWAPP_ADDIPMODAL_H
