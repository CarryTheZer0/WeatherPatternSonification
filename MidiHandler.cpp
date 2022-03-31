#include "MidiHandler.h"
#include "MidiCallBack.h"
#include "MainComponent.h"

MidiHandler::MidiHandler(MainComponent* pOwner) :
    m_pOwner(pOwner)
{}

void MidiHandler::handleIncomingMidiMessage(juce::MidiInput* source, const juce::MidiMessage& message)
{
    postMessage(message, source->getName());
}

void MidiHandler::setMidiInput(juce::AudioDeviceManager* deviceManager)
{
    auto midiInputs = juce::MidiInput::getAvailableDevices();

    auto midiInput = midiInputs[0];

    if (!deviceManager->isMidiInputDeviceEnabled(midiInput.identifier))
        deviceManager->setMidiInputDeviceEnabled(midiInput.identifier, true);

    deviceManager->addMidiInputDeviceCallback(midiInput.identifier, this);
}

void MidiHandler::postMessage(const juce::MidiMessage& message, const juce::String& source)
{
    (new MidiCallback(m_pOwner, message, source))->post();
}