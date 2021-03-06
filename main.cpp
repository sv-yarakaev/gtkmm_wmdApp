
#include "MainWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    //Загрузка файла описания пользовательского интерфейса с помощью экземпляра класса Gtk::Builder
    // и создание экземпляров классов описанных в этом файле виджетов:
    auto refBuilder = Gtk::Builder::create();
    try
    {
        //refBuilder->add_from_file("ui_main.glade");
        // Загрузка из ресурса. Предварительно необходимо скомпилировать файл ресурса res.xml и получить файл resources.c
        // Файл ресурса автоматически добавляется в бинарное приложение
        // glib-compile-resources --target=resources.c --generate-source res.xml
        refBuilder->add_from_resource("/ui/ui_main.glade"); //TODO добавить автокомпиляцию ресурса в CMake


    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }


    MainWindow* pMainWindow = nullptr;
    //Получение созданного с помощью объекта типа Gtk::Builder экземпляра класса окна:
    refBuilder->get_widget_derived("mnWindow", pMainWindow);

    if(pMainWindow)
    {
        app->run(*pMainWindow); //Start:
    }

    delete pMainWindow;

}