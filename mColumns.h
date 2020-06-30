//
// Created by sv.yarakaev on 30.06.2020.
//

#ifndef WINDOWAPP_MCOLUMNS_H
#define WINDOWAPP_MCOLUMNS_H
#include <gtkmm.h>

class ModelColumns : public Gtk::TreeModelColumnRecord {
public:
    ModelColumns();
    Gtk::TreeModelColumn<Glib::ustring> m_col_text;
    Gtk::TreeModelColumn<int> m_col_number;
};


#endif //WINDOWAPP_MCOLUMNS_H
