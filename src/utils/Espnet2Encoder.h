#ifndef GPTINTERFACE_ESPNET2ENCODER_H
#define GPTINTERFACE_ESPNET2ENCODER_H
#include <Python.h>
#define QT_NO_KEYWORDS
#include <QObject>
#include "MediaQueue.h"

class Espnet2Encoder : public QObject
{

    Q_OBJECT

public:
    /**
     * Takes a string and creates a wav fil of espnet2 generated speech.
     * @param lang  : The language of the string - 0 for English, 1 for
     * Japanese.
     * @param input : The Qstring to generate speech from.
     */
    static void textToAudio(const QString &input);
    static void initialize();
    static void finalize();
    /* Pointer to the MediaQueue */
    static MediaQueue *m_mediaQueue;

private:
    /* Pointer to the Python module espnet2. */
    static PyObject* espnetModule;
    /* Pointer to the Python module soundfile. */
    static PyObject* soundfileModule;
    /* Pointer to the espnet2 attribute Text2Speech. */
    static PyObject* text2speech;
    /* Pointer to to from_pretrained attribute */
    static PyObject* from_pretrained;

    /**
    * Determines the language of a string.
     * @return : True is the language is English, false if Japanese.
    */
    static bool checkLanguage(const QString &input);
    //// (4/28/23) TODO: doesn't handle errors/other languages currently.
};

#endif // GPTINTERFACE_ESPNET2ENCODER_H
