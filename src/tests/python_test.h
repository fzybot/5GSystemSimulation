#pragma once

// За основу взята статья https://habr.com/ru/post/466181/

// Необходимо для избежания конфликта со встроенными слотами Qt Slots. 
#undef slots
#include <Python.h>
#define slots Q_SLOTS

// Простое выполнение команды print('Hello')
void python_test(){
    // Загрузка интерпретатора Python
    Py_Initialize();
    // Выполнение команды в интерпретаторе
    PyRun_SimpleString("print('Hello!')");
    // Выгрузка интерпретатора Python
    Py_Finalize();
}

// Выполнение функции из файла simple.py
void python_test_function_file(){
    // Загрузка интерпретатора Python
    Py_Initialize();

    // Выполнение команд в интерпретаторе
    // Загрузка модуля sys
    PyRun_SimpleString("import sys");
    // Подключаем наши исходники python
    PyRun_SimpleString("sys.path.append('/home/ruslan/dev/git/5GSystemSimulation/src/tests')");
    PyRun_SimpleString("import simple");
    PyRun_SimpleString("simple.print_value(2)");
    PyRun_SimpleString("simple.print_value(2.0)");
    PyRun_SimpleString("simple.print_value(\"Hello!\")");
    // Выгрузка интерпретатора Python
    Py_Finalize();
}


// Более слоажная работа с функциями и переменными
void python_test_function_variables(){

}