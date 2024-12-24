#include "speech_recognition_manager.h"

bool GetTextFromSpeech(std::string& text)
{
    using namespace Microsoft::CognitiveServices::Speech;
    using namespace Microsoft::CognitiveServices::Speech::Audio;

    // This example requires environment variables named "SPEECH_KEY" and "SPEECH_REGION"
    auto speechKey = GetEnvironmentalVariable("SPEECH_KEY");
    auto speechRegion = GetEnvironmentalVariable("SPEECH_REGION");

    if ((size(speechKey) == 0) || (size(speechRegion) == 0)) {
        std::cout << speechKey << ", " << speechRegion << std::endl;
        std::cout << "Please set both SPEECH_KEY and SPEECH_REGION environment variables." << std::endl;
        return false;
    }

    auto speechConfig = SpeechConfig::FromSubscription(speechKey, speechRegion);

    speechConfig->SetSpeechRecognitionLanguage("en-US");

    auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
    auto speechRecognizer = SpeechRecognizer::FromConfig(speechConfig, audioConfig);

    std::cout << "Speak into your microphone.\n";
    auto result = speechRecognizer->RecognizeOnceAsync().get();

    if (result->Reason == ResultReason::RecognizedSpeech)
    {
        text = result->Text;
        return true;
    }
    else if (result->Reason == ResultReason::NoMatch)
    {
        std::cout << "NOMATCH: Speech could not be recognized." << std::endl;
        return false;
    }
    else if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = CancellationDetails::FromResult(result);
        std::cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            std::cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            std::cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails << std::endl;
            std::cout << "CANCELED: Did you set the speech resource key and region values?" << std::endl;
        }

        return false;
    }
}

std::string GetEnvironmentalVariable(const char* name)
{
#if defined(_MSC_VER)
    size_t requiredSize = 0;
    (void)getenv_s(&requiredSize, nullptr, 0, name);
    if (requiredSize == 0)
    {
        return "";
    }
    auto buffer = std::make_unique<char[]>(requiredSize);
    (void)getenv_s(&requiredSize, buffer.get(), requiredSize, name);
    return buffer.get();
#else
    auto value = getenv(name);
    return value ? value : "";
#endif
}