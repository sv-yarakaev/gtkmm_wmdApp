//
// Created by sv.yarakaev on 10.06.2020.
//

#include "AddIPModal.h"
#include <iostream>

AddIPModal::AddIPModal() : m_VBox(Gtk::ORIENTATION_VERTICAL),
                           m_Button_Quit("Выход"){
    set_title(" Gtk::TreeView  Gtk::ListStore");
    set_border_width(5);
    set_default_size(400, 200);

    add(m_VBox);

    //Добавление виджета древовидного представления данных в окно прокрутки с кнопкой под ним:
    m_ScrolledWindow.add(m_TreeView);

    //Показывать полосы прокрутки только тогда, когда они необходимы:
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_VBox.pack_start(m_ScrolledWindow);
    m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

    m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
    m_ButtonBox.set_border_width(5);
    m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
    m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
                                                          &AddIPModal::on_button_quit) );

    //Создание модели представления данных:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Заполнение модели представления данных
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "Billy Bob";
    row[m_Columns.m_col_number] = 10;
    row[m_Columns.m_col_percentage] = 15;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "Joey Jojo";
    row[m_Columns.m_col_number] = 20;
    row[m_Columns.m_col_percentage] = 40;

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "Rob McRoberts";
    row[m_Columns.m_col_number] = 30;
    row[m_Columns.m_col_percentage] = 70;

    //Добавление столбцов виджета древовидного представления данных:
    //Числа будут отформатированы стандартным образом.
    m_TreeView.append_column("Ид.", m_Columns.m_col_id);
    m_TreeView.append_column("Имя", m_Columns.m_col_name);

    m_TreeView.append_column_numeric("Отформатированное число", m_Columns.m_col_number,
                                     "%010d" /* 10 цифр, используется заполнение нулями слева. */);

    //Показ индикатора выполнения задачи вместо простого вывода числа:
    Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
    int cols_count = m_TreeView.append_column("Какой-либо показатель", *cell);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count - 1);
    if(pColumn)
    {
        pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
    }

    //Все столбцы делаются перемещаемыми:
    //В этом нет необходимости, но возможность следует продемонстрировать.
    //Вы можете использовать метод TreeView::set_column_drag_function() для
    //реализации более сложного механизма захвата и перемещения.
    for(guint i = 0; i < 2; i++)
    {
        Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
        pColumn->set_reorderable();
    }

    show_all_children();
}

AddIPModal::~AddIPModal() noexcept {

}

void AddIPModal::on_button_quit() {
    hide();
}