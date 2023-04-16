#ifndef GPTINTERFACE_TIKTOKENENCODER_H
#define GPTINTERFACE_TIKTOKENENCODER_H
#include <Python.h>
#define QT_NO_KEYWORDS
#include <QObject>


class TikTokenEncoder : public QObject
{
Q_OBJECT

public:
    explicit TikTokenEncoder(QObject *parent = nullptr);
    ~TikTokenEncoder() override;
    int encode(const std::string &input);

private:
    PyObject* module;
    PyObject* encoding;
};

#endif // GPTINTERFACE_TIKTOKENENCODER_H
