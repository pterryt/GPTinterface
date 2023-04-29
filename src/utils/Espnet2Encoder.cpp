#include "Espnet2Encoder.h"
#include <iostream>

MediaQueue* Espnet2Encoder::m_mediaQueue = nullptr;
PyObject* Espnet2Encoder::espnetModule = nullptr;
PyObject* Espnet2Encoder::soundfileModule = nullptr;
PyObject* Espnet2Encoder::text2speech = nullptr;
PyObject* Espnet2Encoder::from_pretrained = nullptr;

void Espnet2Encoder::initialize()
{
    m_mediaQueue = new MediaQueue();
    Py_Initialize();

    /* Import espnet module */
    espnetModule = PyImport_ImportModule("espnet2.bin.tts_inference");
    if (!espnetModule)
    {
        PyErr_Print();
        std::cerr << "Error: Failed to import espnet2.bin.tts_inference module" << std::endl;
        return;
    }

    /* Get the text2speech class */
    PyObject* class_name = PyUnicode_FromString("Text2Speech");
    text2speech = PyObject_GetAttr(espnetModule, class_name);
    if (!text2speech)
    {
        PyErr_Print();
        std::cerr << "Error: Failed to get Text2Speech attribute from espnetModule" << std::endl;
        Py_DECREF(espnetModule);
        Py_DECREF(class_name);
        return;
    }
    Py_DECREF(class_name);

    /* Get the attribute function from_pretrained */
    from_pretrained = PyObject_GetAttrString(text2speech, "from_pretrained");
    if (from_pretrained == nullptr)
    {
        PyErr_Print();
        std::cerr << "Error: Failed to get from_pretrained attribute from text2speech" << std::endl;
        return;
    }

    /* Get the soundfile module */
    soundfileModule = PyImport_ImportModule("soundfile");
    if (soundfileModule == nullptr)
    {
        std::cerr << "Error: Failed to import soundfile module" << std::endl;
        return;
    }
}


void Espnet2Encoder::finalize()
{
    Py_DECREF(espnetModule);
    Py_DECREF(soundfileModule);
    Py_DECREF(text2speech);
    Py_DECREF(from_pretrained);
    Py_Finalize();
    delete m_mediaQueue;
    m_mediaQueue = nullptr;
}

void Espnet2Encoder::textToAudio(const QString &input)
{
    bool lang = checkLanguage(input);
    /* English and Japanese models, lang param 0, 1 respectively. */
    const char* engModel = "espnet/kan-bayashi_ljspeech_vits";
    const char* jpModel = "mio/amadeus";


    /* Get the model */
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(lang ? engModel : jpModel));
    PyObject* model = PyObject_CallObject(from_pretrained, args);
    if (model == nullptr)
    {
        PyErr_Print();
        std::cerr << "Error: Failed to create Text2Speech instance" << std::endl;
        return;
    }

    /* Pass the string to the model, returns a dictionary */
    std::string strInput = input.toStdString();
    args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(strInput.c_str()));
    PyObject* encode_result = PyObject_CallMethod(model, "__call__", "O", args);

    /* Get the torch.Tensor from the dictionary key "wav" */
    PyObject* tensor_obj = PyDict_GetItemString(encode_result, "wav");
    if (tensor_obj == nullptr) {
        PyErr_Print();
        std::cerr << "Error: Failed to get 'wav' item from the encode_result dictionary" << std::endl;
        Py_DECREF(encode_result);
        Py_DECREF(tensor_obj);
        return;
    }

    /* Create a numpy ndarray from the torch.Tensor */
    PyObject* numpy_array = PyObject_CallMethod(tensor_obj, "numpy", nullptr);
    if (numpy_array == nullptr)
    {
        PyErr_Print();
        std::cerr << "Error: Failed to convert tensor_obj to numpy array" << std::endl;
        Py_DECREF(encode_result);
        Py_DECREF(tensor_obj);
        Py_DECREF(numpy_array);
        return;
    }

    std::string output_file_name = "audio_clips/" + strInput + ".wav";
    const int sample_rate = 22050; // (4/28/23) TODO: get the rate from the dict
    const char* audio_format = "PCM_16";

    /* Create the ouput wav file */
    PyObject* write_result = PyObject_CallMethod(soundfileModule, "write",
                                                 "sOis", output_file_name
                                                 .c_str(), numpy_array,
                                                        sample_rate, audio_format, nullptr);

    if (write_result == nullptr) {
        PyErr_Print();
        std::cerr << "Error: Failed to write audio data to file" << std::endl;
        Py_DECREF(encode_result);
        Py_DECREF(numpy_array);
        return;
    }

    m_mediaQueue->addMedia(QUrl::fromLocalFile(QString::fromStdString(output_file_name)));
    m_mediaQueue->playNext();
//    qDebug() << m_mediaQueue->m_mediaPlayer->isPlaying();
    /* Deallocate resources */
    Py_DECREF(model);
    Py_DECREF(write_result);
    Py_DECREF(args);
    Py_DECREF(tensor_obj);
    Py_DECREF(encode_result);
    Py_DECREF(numpy_array);
}

bool Espnet2Encoder::checkLanguage(const QString &input)
{
    bool is_english = false;
    QChar ch = input.at(0);
    ushort unicode_value = ch.unicode();

    // Check the first character
    if (unicode_value >= 0x3040 && unicode_value <= 0x30FF)
    {
        return false;  // Japanese
    }
    else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) || (unicode_value >= 0x0061 && unicode_value <= 0x007A))
    {
        is_english = true;
    }

    // Check the rest of the string
    for (int i = 1; i < input.length(); i++)
    {
        ch = input[i];
        unicode_value = ch.unicode();
        if (unicode_value >= 0x3040 && unicode_value <= 0x30FF)
        {
            return false;  // Japanese
        }
        else if ((unicode_value >= 0x0041 && unicode_value <= 0x005A) || (unicode_value >= 0x0061 && unicode_value <= 0x007A))
        {
            if (is_english)
            {
                return true;  // English
            }
            else
            {
                is_english = true;
            }
        }
        else
        {
            is_english = false;
        }
    }

    return is_english;
}
