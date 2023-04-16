#include "TikTokenEncoder.h"
#include <iostream>

TikTokenEncoder::TikTokenEncoder(QObject *parent)
        : QObject(parent)
{
    Py_Initialize();
    module = PyImport_ImportModule("tiktoken");
    encoding = PyObject_CallMethod(module, "get_encoding", "s", "cl100k_base");

}

TikTokenEncoder::~TikTokenEncoder()
{
    Py_DECREF(module);
    Py_DECREF(encoding);
    Py_Finalize();
}

int TikTokenEncoder::encode(const std::string &input)
{
   PyObject* encoded_text = PyObject_CallMethod(encoding, "encode", "s",
                                                input.c_str());
   int length = static_cast<int>(PyList_Size(encoded_text));
   Py_DECREF(encoded_text);

   return length;
}