/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#include "RNBO_Common.h"
#include "RNBO_AudioSignal.h"

namespace RNBO {


#define trunc(x) ((Int)(x))

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

class rnbomatic : public PatcherInterfaceImpl {
public:

rnbomatic()
{
}

~rnbomatic()
{
}

rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -217479832, false);
    getEngine()->flushClockEvents(this, -1093754261, false);
    getEngine()->flushClockEvents(this, -1735137014, false);
    getEngine()->flushClockEvents(this, 2061648746, false);
    getEngine()->flushClockEvents(this, 922084457, false);
    getEngine()->flushClockEvents(this, -1357044121, false);
    getEngine()->flushClockEvents(this, -871642103, false);
    getEngine()->flushClockEvents(this, -1494586265, false);
}

template <typename T> void listquicksort(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template <typename T> Int listpartition(T& arr, T& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template <typename T> void listswapelements(T& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number safepow(number base, number exponent) {
    return fixnan(rnbo_pow(base, exponent));
}

number scale(
    number x,
    number lowin,
    number hiin,
    number lowout,
    number highout,
    number pow
) {
    auto inscale = this->safediv(1., hiin - lowin);
    number outdiff = highout - lowout;
    number value = (x - lowin) * inscale;

    if (pow != 1) {
        if (value > 0)
            value = this->safepow(value, pow);
        else
            value = -this->safepow(-value, pow);
    }

    value = value * outdiff + lowout;
    return value;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

number samplerate() const {
    return this->sr;
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

Index vectorsize() const {
    return this->vs;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    RNBO_UNUSED(numInputs);
    RNBO_UNUSED(inputs);
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime());
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
    SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
    SampleValue * out5 = (numOutputs >= 5 && outputs[4] ? outputs[4] : this->dummyBuffer);
    SampleValue * out6 = (numOutputs >= 6 && outputs[5] ? outputs[5] : this->dummyBuffer);
    SampleValue * out7 = (numOutputs >= 7 && outputs[6] ? outputs[6] : this->dummyBuffer);
    SampleValue * out8 = (numOutputs >= 8 && outputs[7] ? outputs[7] : this->dummyBuffer);
    SampleValue * out9 = (numOutputs >= 9 && outputs[8] ? outputs[8] : this->dummyBuffer);
    SampleValue * out10 = (numOutputs >= 10 && outputs[9] ? outputs[9] : this->dummyBuffer);
    SampleValue * out11 = (numOutputs >= 11 && outputs[10] ? outputs[10] : this->dummyBuffer);
    SampleValue * out12 = (numOutputs >= 12 && outputs[11] ? outputs[11] : this->dummyBuffer);
    SampleValue * out13 = (numOutputs >= 13 && outputs[12] ? outputs[12] : this->dummyBuffer);
    SampleValue * out14 = (numOutputs >= 14 && outputs[13] ? outputs[13] : this->dummyBuffer);
    SampleValue * out15 = (numOutputs >= 15 && outputs[14] ? outputs[14] : this->dummyBuffer);
    SampleValue * out16 = (numOutputs >= 16 && outputs[15] ? outputs[15] : this->dummyBuffer);

    this->groove_01_perform(
        this->groove_01_rate_auto,
        this->groove_01_begin,
        this->groove_01_end,
        this->signals[0],
        this->signals[1],
        n
    );

    this->gaintilde_01_perform(this->signals[0], out1, n);
    this->gaintilde_02_perform(this->signals[1], out2, n);
    this->gaintilde_03_perform(this->zeroBuffer, out3, n);
    this->gaintilde_04_perform(this->zeroBuffer, out4, n);
    this->gaintilde_05_perform(this->zeroBuffer, out5, n);
    this->gaintilde_06_perform(this->zeroBuffer, out6, n);
    this->gaintilde_07_perform(this->zeroBuffer, out7, n);
    this->gaintilde_08_perform(this->zeroBuffer, out8, n);
    this->gaintilde_09_perform(this->zeroBuffer, out9, n);
    this->gaintilde_10_perform(this->zeroBuffer, out10, n);
    this->gaintilde_11_perform(this->zeroBuffer, out11, n);
    this->gaintilde_12_perform(this->zeroBuffer, out12, n);
    this->gaintilde_13_perform(this->zeroBuffer, out13, n);
    this->gaintilde_14_perform(this->zeroBuffer, out14, n);
    this->gaintilde_15_perform(this->zeroBuffer, out15, n);
    this->gaintilde_16_perform(this->zeroBuffer, out16, n);
    this->dspexpr_01_perform(this->dspexpr_01_in1, this->dspexpr_01_in2, this->signals[1], n);
    this->numbertilde_01_perform(this->signals[1], this->dummyBuffer, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 2; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->groove_01_dspsetup(forceDSPSetup);
    this->gaintilde_01_dspsetup(forceDSPSetup);
    this->gaintilde_02_dspsetup(forceDSPSetup);
    this->gaintilde_03_dspsetup(forceDSPSetup);
    this->gaintilde_04_dspsetup(forceDSPSetup);
    this->gaintilde_05_dspsetup(forceDSPSetup);
    this->gaintilde_06_dspsetup(forceDSPSetup);
    this->gaintilde_07_dspsetup(forceDSPSetup);
    this->gaintilde_08_dspsetup(forceDSPSetup);
    this->gaintilde_09_dspsetup(forceDSPSetup);
    this->data_01_dspsetup(forceDSPSetup);
    this->gaintilde_10_dspsetup(forceDSPSetup);
    this->gaintilde_11_dspsetup(forceDSPSetup);
    this->gaintilde_12_dspsetup(forceDSPSetup);
    this->gaintilde_13_dspsetup(forceDSPSetup);
    this->gaintilde_14_dspsetup(forceDSPSetup);
    this->gaintilde_15_dspsetup(forceDSPSetup);
    this->gaintilde_16_dspsetup(forceDSPSetup);
    this->numbertilde_01_dspsetup(forceDSPSetup);
    this->data_02_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

void setProbingTarget(MessageTag id) {
    switch (id) {
    default:
        {
        this->setProbingIndex(-1);
        break;
        }
    }
}

void setProbingIndex(ProbingIndex ) {}

Index getProbingChannels(MessageTag outletId) const {
    RNBO_UNUSED(outletId);
    return 0;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->playback);
        break;
        }
    case 1:
        {
        return addressOf(this->b_audio_wav);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 2;
}

void fillDataRef(DataRefIndex , DataRef& ) {}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time);

    if (index == 0) {
        this->groove_01_buffer = new Float32Buffer(this->playback);
        this->data_01_buffer = new Float32Buffer(this->playback);
        this->data_01_bufferUpdated();
    }

    if (index == 1) {
        this->data_02_buffer = new Float32Buffer(this->b_audio_wav);
        this->data_02_bufferUpdated();
    }
}

void initialize() {
    this->playback = initDataRef("playback", false, nullptr, "buffer~");
    this->b_audio_wav = initDataRef("b_audio_wav", false, "/Users/josue/Downloads/audio.wav", "buffer~");
    this->assign_defaults();
    this->setState();
    this->playback->setIndex(0);
    this->groove_01_buffer = new Float32Buffer(this->playback);
    this->data_01_buffer = new Float32Buffer(this->playback);
    this->b_audio_wav->setIndex(1);
    this->data_02_buffer = new Float32Buffer(this->b_audio_wav);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

Index getPatcherSerial() const {
    return 0;
}

void getState(PatcherStateInterface& ) {}

void setState() {}

void getPreset(PatcherStateInterface& preset) {
    preset["__presetid"] = "rnbo";
}

void setPreset(MillisecondTime , PatcherStateInterface& ) {}

void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    default:
        {
        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 0;
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    default:
        {
        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    default:
        {
        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    default:
        {
        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    default:
        {
        return value;
        }
    }
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time);

    switch (index) {
    case -217479832:
        {
        this->delay_01_out_bang();
        break;
        }
    case -1093754261:
        {
        this->delay_02_out_bang();
        break;
        }
    case -1735137014:
        {
        this->loadbang_01_startupbang_bang();
        break;
        }
    case 2061648746:
        {
        this->delay_03_out_bang();
        break;
        }
    case 922084457:
        {
        this->delay_04_out_bang();
        break;
        }
    case -1357044121:
        {
        this->delay_05_out_bang();
        break;
        }
    case -871642103:
        {
        this->loadbang_02_startupbang_bang();
        break;
        }
    case -1494586265:
        {
        this->numbertilde_01_value_set(value);
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time);
    this->processOutletAtCurrentTime(sender, index, value);
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time);

    switch (tag) {
    case TAG("consultaInfo"):
        {
        this->inport_01_value_number_set(payload);
        break;
        }
    case TAG("valin"):
        {
        if (TAG("gain~_obj-48") == objectId)
            this->gaintilde_01_valin_set(payload);

        if (TAG("gain~_obj-36") == objectId)
            this->gaintilde_02_valin_set(payload);

        if (TAG("gain~_obj-38") == objectId)
            this->gaintilde_03_valin_set(payload);

        if (TAG("gain~_obj-37") == objectId)
            this->gaintilde_04_valin_set(payload);

        if (TAG("number_obj-3") == objectId)
            this->numberobj_01_valin_set(payload);

        if (TAG("gain~_obj-42") == objectId)
            this->gaintilde_05_valin_set(payload);

        if (TAG("gain~_obj-41") == objectId)
            this->gaintilde_06_valin_set(payload);

        if (TAG("gain~_obj-40") == objectId)
            this->gaintilde_07_valin_set(payload);

        if (TAG("gain~_obj-39") == objectId)
            this->gaintilde_08_valin_set(payload);

        if (TAG("toggle_obj-14") == objectId)
            this->toggle_01_valin_set(payload);

        if (TAG("gain~_obj-51") == objectId)
            this->gaintilde_09_valin_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_02_valin_set(payload);

        if (TAG("gain~_obj-50") == objectId)
            this->gaintilde_10_valin_set(payload);

        if (TAG("gain~_obj-49") == objectId)
            this->gaintilde_11_valin_set(payload);

        if (TAG("number_obj-4") == objectId)
            this->numberobj_03_valin_set(payload);

        if (TAG("gain~_obj-47") == objectId)
            this->gaintilde_12_valin_set(payload);

        if (TAG("gain~_obj-46") == objectId)
            this->gaintilde_13_valin_set(payload);

        if (TAG("number_obj-113") == objectId)
            this->numberobj_04_valin_set(payload);

        if (TAG("gain~_obj-45") == objectId)
            this->gaintilde_14_valin_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_05_valin_set(payload);

        if (TAG("gain~_obj-44") == objectId)
            this->gaintilde_15_valin_set(payload);

        if (TAG("gain~_obj-43") == objectId)
            this->gaintilde_16_valin_set(payload);

        if (TAG("number_obj-152") == objectId)
            this->numberobj_06_valin_set(payload);

        if (TAG("number_obj-159") == objectId)
            this->numberobj_07_valin_set(payload);

        if (TAG("number_obj-60") == objectId)
            this->numberobj_08_valin_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_09_valin_set(payload);

        if (TAG("number_obj-143") == objectId)
            this->numberobj_10_valin_set(payload);

        if (TAG("number_obj-85") == objectId)
            this->numberobj_11_valin_set(payload);

        if (TAG("number_obj-144") == objectId)
            this->numberobj_12_valin_set(payload);

        if (TAG("number_obj-92") == objectId)
            this->numberobj_13_valin_set(payload);

        if (TAG("number_obj-146") == objectId)
            this->numberobj_14_valin_set(payload);

        if (TAG("number_obj-89") == objectId)
            this->numberobj_15_valin_set(payload);

        if (TAG("number_obj-148") == objectId)
            this->numberobj_16_valin_set(payload);

        if (TAG("number_obj-107") == objectId)
            this->numberobj_17_valin_set(payload);

        if (TAG("number_obj-149") == objectId)
            this->numberobj_18_valin_set(payload);

        if (TAG("number_obj-102") == objectId)
            this->numberobj_19_valin_set(payload);

        if (TAG("number_obj-151") == objectId)
            this->numberobj_20_valin_set(payload);

        if (TAG("number_obj-99") == objectId)
            this->numberobj_21_valin_set(payload);

        if (TAG("number_obj-153") == objectId)
            this->numberobj_22_valin_set(payload);

        if (TAG("number_obj-95") == objectId)
            this->numberobj_23_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-3") == objectId)
            this->numberobj_01_format_set(payload);

        if (TAG("number_obj-6") == objectId)
            this->numberobj_02_format_set(payload);

        if (TAG("number_obj-4") == objectId)
            this->numberobj_03_format_set(payload);

        if (TAG("number_obj-113") == objectId)
            this->numberobj_04_format_set(payload);

        if (TAG("number_obj-103") == objectId)
            this->numberobj_05_format_set(payload);

        if (TAG("number_obj-152") == objectId)
            this->numberobj_06_format_set(payload);

        if (TAG("number_obj-159") == objectId)
            this->numberobj_07_format_set(payload);

        if (TAG("number_obj-60") == objectId)
            this->numberobj_08_format_set(payload);

        if (TAG("number_obj-136") == objectId)
            this->numberobj_09_format_set(payload);

        if (TAG("number_obj-143") == objectId)
            this->numberobj_10_format_set(payload);

        if (TAG("number_obj-85") == objectId)
            this->numberobj_11_format_set(payload);

        if (TAG("number_obj-144") == objectId)
            this->numberobj_12_format_set(payload);

        if (TAG("number_obj-92") == objectId)
            this->numberobj_13_format_set(payload);

        if (TAG("number_obj-146") == objectId)
            this->numberobj_14_format_set(payload);

        if (TAG("number_obj-89") == objectId)
            this->numberobj_15_format_set(payload);

        if (TAG("number_obj-148") == objectId)
            this->numberobj_16_format_set(payload);

        if (TAG("number_obj-107") == objectId)
            this->numberobj_17_format_set(payload);

        if (TAG("number_obj-149") == objectId)
            this->numberobj_18_format_set(payload);

        if (TAG("number_obj-102") == objectId)
            this->numberobj_19_format_set(payload);

        if (TAG("number_obj-151") == objectId)
            this->numberobj_20_format_set(payload);

        if (TAG("number_obj-99") == objectId)
            this->numberobj_21_format_set(payload);

        if (TAG("number_obj-153") == objectId)
            this->numberobj_22_format_set(payload);

        if (TAG("number_obj-95") == objectId)
            this->numberobj_23_format_set(payload);

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-15") == objectId)
            this->message_01_listin_number_set(payload);

        if (TAG("message_obj-130") == objectId)
            this->message_02_listin_number_set(payload);

        break;
        }
    case TAG("sig"):
        {
        if (TAG("number~_obj-147") == objectId)
            this->numbertilde_01_sig_number_set(payload);

        break;
        }
    case TAG("mode"):
        {
        if (TAG("number~_obj-147") == objectId)
            this->numbertilde_01_mode_set(payload);

        break;
        }
    case TAG("/vol1"):
        {
        this->inport_02_value_number_set(payload);
        break;
        }
    case TAG("/vol2"):
        {
        this->inport_03_value_number_set(payload);
        break;
        }
    case TAG("/vol3"):
        {
        this->inport_04_value_number_set(payload);
        break;
        }
    case TAG("/vol4"):
        {
        this->inport_05_value_number_set(payload);
        break;
        }
    case TAG("/vol5"):
        {
        this->inport_06_value_number_set(payload);
        break;
        }
    case TAG("/vol6"):
        {
        this->inport_07_value_number_set(payload);
        break;
        }
    case TAG("/vol7"):
        {
        this->inport_08_value_number_set(payload);
        break;
        }
    case TAG("/vol8"):
        {
        this->inport_09_value_number_set(payload);
        break;
        }
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time);

    switch (tag) {
    case TAG("consultaInfo"):
        {
        this->inport_01_value_list_set(payload);
        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-15") == objectId)
            this->message_01_listin_list_set(payload);

        if (TAG("message_obj-130") == objectId)
            this->message_02_listin_list_set(payload);

        break;
        }
    case TAG("sig"):
        {
        if (TAG("number~_obj-147") == objectId)
            this->numbertilde_01_sig_list_set(payload);

        break;
        }
    case TAG("/vol1"):
        {
        this->inport_02_value_list_set(payload);
        break;
        }
    case TAG("/vol2"):
        {
        this->inport_03_value_list_set(payload);
        break;
        }
    case TAG("/vol3"):
        {
        this->inport_04_value_list_set(payload);
        break;
        }
    case TAG("/vol4"):
        {
        this->inport_05_value_list_set(payload);
        break;
        }
    case TAG("/vol5"):
        {
        this->inport_06_value_list_set(payload);
        break;
        }
    case TAG("/vol6"):
        {
        this->inport_07_value_list_set(payload);
        break;
        }
    case TAG("/vol7"):
        {
        this->inport_08_value_list_set(payload);
        break;
        }
    case TAG("/vol8"):
        {
        this->inport_09_value_list_set(payload);
        break;
        }
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time);

    switch (tag) {
    case TAG("consultaInfo"):
        {
        this->inport_01_value_bang_bang();
        break;
        }
    case TAG("bangin"):
        {
        if (TAG("button_obj-118") == objectId)
            this->button_01_bangin_bang();

        if (TAG("button_obj-17") == objectId)
            this->button_02_bangin_bang();

        break;
        }
    case TAG("startupbang"):
        {
        if (TAG("loadbang_obj-9") == objectId)
            this->loadbang_01_startupbang_bang();

        if (TAG("loadbang_obj-131") == objectId)
            this->loadbang_02_startupbang_bang();

        break;
        }
    case TAG("listin"):
        {
        if (TAG("message_obj-15") == objectId)
            this->message_01_listin_bang_bang();

        if (TAG("message_obj-130") == objectId)
            this->message_02_listin_bang_bang();

        break;
        }
    case TAG("/vol1"):
        {
        this->inport_02_value_bang_bang();
        break;
        }
    case TAG("/vol2"):
        {
        this->inport_03_value_bang_bang();
        break;
        }
    case TAG("/vol3"):
        {
        this->inport_04_value_bang_bang();
        break;
        }
    case TAG("/vol4"):
        {
        this->inport_05_value_bang_bang();
        break;
        }
    case TAG("/vol5"):
        {
        this->inport_06_value_bang_bang();
        break;
        }
    case TAG("/vol6"):
        {
        this->inport_07_value_bang_bang();
        break;
        }
    case TAG("/vol7"):
        {
        this->inport_08_value_bang_bang();
        break;
        }
    case TAG("/vol8"):
        {
        this->inport_09_value_bang_bang();
        break;
        }
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("bangout"):
        {
        return "bangout";
        }
    case TAG("button_obj-118"):
        {
        return "button_obj-118";
        }
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("gain~_obj-48"):
        {
        return "gain~_obj-48";
        }
    case TAG("button_obj-17"):
        {
        return "button_obj-17";
        }
    case TAG("gain~_obj-36"):
        {
        return "gain~_obj-36";
        }
    case TAG("gain~_obj-38"):
        {
        return "gain~_obj-38";
        }
    case TAG("gain~_obj-37"):
        {
        return "gain~_obj-37";
        }
    case TAG("number_obj-3"):
        {
        return "number_obj-3";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-15"):
        {
        return "message_obj-15";
        }
    case TAG("gain~_obj-42"):
        {
        return "gain~_obj-42";
        }
    case TAG("gain~_obj-41"):
        {
        return "gain~_obj-41";
        }
    case TAG("gain~_obj-40"):
        {
        return "gain~_obj-40";
        }
    case TAG("gain~_obj-39"):
        {
        return "gain~_obj-39";
        }
    case TAG("toggle_obj-14"):
        {
        return "toggle_obj-14";
        }
    case TAG("gain~_obj-51"):
        {
        return "gain~_obj-51";
        }
    case TAG("number_obj-6"):
        {
        return "number_obj-6";
        }
    case TAG("gain~_obj-50"):
        {
        return "gain~_obj-50";
        }
    case TAG("gain~_obj-49"):
        {
        return "gain~_obj-49";
        }
    case TAG("channels"):
        {
        return "channels";
        }
    case TAG(""):
        {
        return "";
        }
    case TAG("number_obj-4"):
        {
        return "number_obj-4";
        }
    case TAG("gain~_obj-47"):
        {
        return "gain~_obj-47";
        }
    case TAG("gain~_obj-46"):
        {
        return "gain~_obj-46";
        }
    case TAG("number_obj-113"):
        {
        return "number_obj-113";
        }
    case TAG("gain~_obj-45"):
        {
        return "gain~_obj-45";
        }
    case TAG("loopeando"):
        {
        return "loopeando";
        }
    case TAG("number_obj-103"):
        {
        return "number_obj-103";
        }
    case TAG("gain~_obj-44"):
        {
        return "gain~_obj-44";
        }
    case TAG("gain~_obj-43"):
        {
        return "gain~_obj-43";
        }
    case TAG("monitor"):
        {
        return "monitor";
        }
    case TAG("number~_obj-147"):
        {
        return "number~_obj-147";
        }
    case TAG("assign"):
        {
        return "assign";
        }
    case TAG("number_obj-152"):
        {
        return "number_obj-152";
        }
    case TAG("seg"):
        {
        return "seg";
        }
    case TAG("number_obj-159"):
        {
        return "number_obj-159";
        }
    case TAG("durSeg"):
        {
        return "durSeg";
        }
    case TAG("message_obj-130"):
        {
        return "message_obj-130";
        }
    case TAG("number_obj-60"):
        {
        return "number_obj-60";
        }
    case TAG("number_obj-136"):
        {
        return "number_obj-136";
        }
    case TAG("volumen1"):
        {
        return "volumen1";
        }
    case TAG("number_obj-143"):
        {
        return "number_obj-143";
        }
    case TAG("volumen2"):
        {
        return "volumen2";
        }
    case TAG("number_obj-85"):
        {
        return "number_obj-85";
        }
    case TAG("number_obj-144"):
        {
        return "number_obj-144";
        }
    case TAG("volumen3"):
        {
        return "volumen3";
        }
    case TAG("number_obj-92"):
        {
        return "number_obj-92";
        }
    case TAG("number_obj-146"):
        {
        return "number_obj-146";
        }
    case TAG("volumen4"):
        {
        return "volumen4";
        }
    case TAG("number_obj-89"):
        {
        return "number_obj-89";
        }
    case TAG("number_obj-148"):
        {
        return "number_obj-148";
        }
    case TAG("volumen5"):
        {
        return "volumen5";
        }
    case TAG("number_obj-107"):
        {
        return "number_obj-107";
        }
    case TAG("number_obj-149"):
        {
        return "number_obj-149";
        }
    case TAG("volumen6"):
        {
        return "volumen6";
        }
    case TAG("number_obj-102"):
        {
        return "number_obj-102";
        }
    case TAG("number_obj-151"):
        {
        return "number_obj-151";
        }
    case TAG("volumen7"):
        {
        return "volumen7";
        }
    case TAG("number_obj-99"):
        {
        return "number_obj-99";
        }
    case TAG("number_obj-153"):
        {
        return "number_obj-153";
        }
    case TAG("volumen8"):
        {
        return "volumen8";
        }
    case TAG("number_obj-95"):
        {
        return "number_obj-95";
        }
    case TAG("consultaInfo"):
        {
        return "consultaInfo";
        }
    case TAG("bangin"):
        {
        return "bangin";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("startupbang"):
        {
        return "startupbang";
        }
    case TAG("loadbang_obj-9"):
        {
        return "loadbang_obj-9";
        }
    case TAG("format"):
        {
        return "format";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    case TAG("sig"):
        {
        return "sig";
        }
    case TAG("mode"):
        {
        return "mode";
        }
    case TAG("loadbang_obj-131"):
        {
        return "loadbang_obj-131";
        }
    case TAG("/vol1"):
        {
        return "/vol1";
        }
    case TAG("/vol2"):
        {
        return "/vol2";
        }
    case TAG("/vol3"):
        {
        return "/vol3";
        }
    case TAG("/vol4"):
        {
        return "/vol4";
        }
    case TAG("/vol5"):
        {
        return "/vol5";
        }
    case TAG("/vol6"):
        {
        return "/vol6";
        }
    case TAG("/vol7"):
        {
        return "/vol7";
        }
    case TAG("/vol8"):
        {
        return "/vol8";
        }
    }

    return "";
}

MessageIndex getNumMessages() const {
    return 21;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        {
        static const MessageInfo r0 = {
            "channels",
            Outport
        };

        return r0;
        }
    case 1:
        {
        static const MessageInfo r1 = {
            "loopeando",
            Outport
        };

        return r1;
        }
    case 2:
        {
        static const MessageInfo r2 = {
            "seg",
            Outport
        };

        return r2;
        }
    case 3:
        {
        static const MessageInfo r3 = {
            "durSeg",
            Outport
        };

        return r3;
        }
    case 4:
        {
        static const MessageInfo r4 = {
            "volumen1",
            Outport
        };

        return r4;
        }
    case 5:
        {
        static const MessageInfo r5 = {
            "volumen2",
            Outport
        };

        return r5;
        }
    case 6:
        {
        static const MessageInfo r6 = {
            "volumen3",
            Outport
        };

        return r6;
        }
    case 7:
        {
        static const MessageInfo r7 = {
            "volumen4",
            Outport
        };

        return r7;
        }
    case 8:
        {
        static const MessageInfo r8 = {
            "volumen5",
            Outport
        };

        return r8;
        }
    case 9:
        {
        static const MessageInfo r9 = {
            "volumen6",
            Outport
        };

        return r9;
        }
    case 10:
        {
        static const MessageInfo r10 = {
            "volumen7",
            Outport
        };

        return r10;
        }
    case 11:
        {
        static const MessageInfo r11 = {
            "volumen8",
            Outport
        };

        return r11;
        }
    case 12:
        {
        static const MessageInfo r12 = {
            "consultaInfo",
            Inport
        };

        return r12;
        }
    case 13:
        {
        static const MessageInfo r13 = {
            "/vol1",
            Inport
        };

        return r13;
        }
    case 14:
        {
        static const MessageInfo r14 = {
            "/vol2",
            Inport
        };

        return r14;
        }
    case 15:
        {
        static const MessageInfo r15 = {
            "/vol3",
            Inport
        };

        return r15;
        }
    case 16:
        {
        static const MessageInfo r16 = {
            "/vol4",
            Inport
        };

        return r16;
        }
    case 17:
        {
        static const MessageInfo r17 = {
            "/vol5",
            Inport
        };

        return r17;
        }
    case 18:
        {
        static const MessageInfo r18 = {
            "/vol6",
            Inport
        };

        return r18;
        }
    case 19:
        {
        static const MessageInfo r19 = {
            "/vol7",
            Inport
        };

        return r19;
        }
    case 20:
        {
        static const MessageInfo r20 = {
            "/vol8",
            Inport
        };

        return r20;
        }
    }

    return NullMessageInfo;
}

protected:

void delay_01_out_bang() {
    this->numberobj_05_value_bang();
    this->message_01_trigger_bang();
}

void inport_01_value_bang_bang() {
    this->inport_01_out_bang_bang();
}

void inport_01_value_number_set(number v) {
    this->inport_01_out_number_set(v);
}

void inport_01_value_list_set(const list& v) {
    this->inport_01_out_list_set(v);
}

void button_01_bangin_bang() {
    this->button_01_bangval_bang();
}

void gaintilde_01_valin_set(number v) {
    this->gaintilde_01_value_set(v);
}

void delay_02_out_bang() {
    this->button_02_bangval_bang();
}

void button_02_bangin_bang() {
    this->button_02_bangval_bang();
}

void loadbang_01_startupbang_bang() {
    this->loadbang_01_output_bang();
}

void gaintilde_02_valin_set(number v) {
    this->gaintilde_02_value_set(v);
}

void gaintilde_03_valin_set(number v) {
    this->gaintilde_03_value_set(v);
}

void delay_03_out_bang() {
    this->data_02_info_bang();
}

void gaintilde_04_valin_set(number v) {
    this->gaintilde_04_value_set(v);
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void message_01_listin_list_set(const list& v) {
    this->message_01_set_set(v);
}

void message_01_listin_number_set(number v) {
    this->message_01_set_set(v);
}

void message_01_listin_bang_bang() {
    this->message_01_trigger_bang();
}

void gaintilde_05_valin_set(number v) {
    this->gaintilde_05_value_set(v);
}

void gaintilde_06_valin_set(number v) {
    this->gaintilde_06_value_set(v);
}

void gaintilde_07_valin_set(number v) {
    this->gaintilde_07_value_set(v);
}

void gaintilde_08_valin_set(number v) {
    this->gaintilde_08_value_set(v);
}

void delay_04_out_bang() {
    this->toggle_01_value_bang_bang();
}

void toggle_01_valin_set(number v) {
    this->toggle_01_value_number_set(v);
}

void gaintilde_09_valin_set(number v) {
    this->gaintilde_09_value_set(v);
}

void numberobj_02_valin_set(number v) {
    this->numberobj_02_value_set(v);
}

void numberobj_02_format_set(number v) {
    this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void gaintilde_10_valin_set(number v) {
    this->gaintilde_10_value_set(v);
}

void gaintilde_11_valin_set(number v) {
    this->gaintilde_11_value_set(v);
}

void numberobj_03_valin_set(number v) {
    this->numberobj_03_value_set(v);
}

void numberobj_03_format_set(number v) {
    this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void gaintilde_12_valin_set(number v) {
    this->gaintilde_12_value_set(v);
}

void gaintilde_13_valin_set(number v) {
    this->gaintilde_13_value_set(v);
}

void numberobj_04_valin_set(number v) {
    this->numberobj_04_value_set(v);
}

void numberobj_04_format_set(number v) {
    this->numberobj_04_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void gaintilde_14_valin_set(number v) {
    this->gaintilde_14_value_set(v);
}

void numberobj_05_valin_set(number v) {
    this->numberobj_05_value_set(v);
}

void numberobj_05_format_set(number v) {
    this->numberobj_05_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void gaintilde_15_valin_set(number v) {
    this->gaintilde_15_value_set(v);
}

void gaintilde_16_valin_set(number v) {
    this->gaintilde_16_value_set(v);
}

void numbertilde_01_sig_number_set(number v) {
    this->numbertilde_01_outValue = v;
}

void numbertilde_01_sig_list_set(const list& v) {
    this->numbertilde_01_outValue = v[0];
}

void numbertilde_01_mode_set(number v) {
    if (v == 1) {
        this->numbertilde_01_currentMode = 0;
    } else if (v == 2) {
        this->numbertilde_01_currentMode = 1;
    }
}

void numberobj_06_valin_set(number v) {
    this->numberobj_06_value_set(v);
}

void numberobj_06_format_set(number v) {
    this->numberobj_06_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_07_valin_set(number v) {
    this->numberobj_07_value_set(v);
}

void numberobj_07_format_set(number v) {
    this->numberobj_07_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void delay_05_out_bang() {
    this->message_02_trigger_bang();
}

void loadbang_02_startupbang_bang() {
    this->loadbang_02_output_bang();
}

void message_02_listin_list_set(const list& v) {
    this->message_02_set_set(v);
}

void message_02_listin_number_set(number v) {
    this->message_02_set_set(v);
}

void message_02_listin_bang_bang() {
    this->message_02_trigger_bang();
}

void numberobj_08_valin_set(number v) {
    this->numberobj_08_value_set(v);
}

void numberobj_08_format_set(number v) {
    this->numberobj_08_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_09_valin_set(number v) {
    this->numberobj_09_value_set(v);
}

void numberobj_09_format_set(number v) {
    this->numberobj_09_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_02_value_bang_bang() {
    this->inport_02_out_bang_bang();
}

void inport_02_value_number_set(number v) {
    this->inport_02_out_number_set(v);
}

void inport_02_value_list_set(const list& v) {
    this->inport_02_out_list_set(v);
}

void numberobj_10_valin_set(number v) {
    this->numberobj_10_value_set(v);
}

void numberobj_10_format_set(number v) {
    this->numberobj_10_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_11_valin_set(number v) {
    this->numberobj_11_value_set(v);
}

void numberobj_11_format_set(number v) {
    this->numberobj_11_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_03_value_bang_bang() {
    this->inport_03_out_bang_bang();
}

void inport_03_value_number_set(number v) {
    this->inport_03_out_number_set(v);
}

void inport_03_value_list_set(const list& v) {
    this->inport_03_out_list_set(v);
}

void numberobj_12_valin_set(number v) {
    this->numberobj_12_value_set(v);
}

void numberobj_12_format_set(number v) {
    this->numberobj_12_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_13_valin_set(number v) {
    this->numberobj_13_value_set(v);
}

void numberobj_13_format_set(number v) {
    this->numberobj_13_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_04_value_bang_bang() {
    this->inport_04_out_bang_bang();
}

void inport_04_value_number_set(number v) {
    this->inport_04_out_number_set(v);
}

void inport_04_value_list_set(const list& v) {
    this->inport_04_out_list_set(v);
}

void numberobj_14_valin_set(number v) {
    this->numberobj_14_value_set(v);
}

void numberobj_14_format_set(number v) {
    this->numberobj_14_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_15_valin_set(number v) {
    this->numberobj_15_value_set(v);
}

void numberobj_15_format_set(number v) {
    this->numberobj_15_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_05_value_bang_bang() {
    this->inport_05_out_bang_bang();
}

void inport_05_value_number_set(number v) {
    this->inport_05_out_number_set(v);
}

void inport_05_value_list_set(const list& v) {
    this->inport_05_out_list_set(v);
}

void numberobj_16_valin_set(number v) {
    this->numberobj_16_value_set(v);
}

void numberobj_16_format_set(number v) {
    this->numberobj_16_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_17_valin_set(number v) {
    this->numberobj_17_value_set(v);
}

void numberobj_17_format_set(number v) {
    this->numberobj_17_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_06_value_bang_bang() {
    this->inport_06_out_bang_bang();
}

void inport_06_value_number_set(number v) {
    this->inport_06_out_number_set(v);
}

void inport_06_value_list_set(const list& v) {
    this->inport_06_out_list_set(v);
}

void numberobj_18_valin_set(number v) {
    this->numberobj_18_value_set(v);
}

void numberobj_18_format_set(number v) {
    this->numberobj_18_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_19_valin_set(number v) {
    this->numberobj_19_value_set(v);
}

void numberobj_19_format_set(number v) {
    this->numberobj_19_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_07_value_bang_bang() {
    this->inport_07_out_bang_bang();
}

void inport_07_value_number_set(number v) {
    this->inport_07_out_number_set(v);
}

void inport_07_value_list_set(const list& v) {
    this->inport_07_out_list_set(v);
}

void numberobj_20_valin_set(number v) {
    this->numberobj_20_value_set(v);
}

void numberobj_20_format_set(number v) {
    this->numberobj_20_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_21_valin_set(number v) {
    this->numberobj_21_value_set(v);
}

void numberobj_21_format_set(number v) {
    this->numberobj_21_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_08_value_bang_bang() {
    this->inport_08_out_bang_bang();
}

void inport_08_value_number_set(number v) {
    this->inport_08_out_number_set(v);
}

void inport_08_value_list_set(const list& v) {
    this->inport_08_out_list_set(v);
}

void numberobj_22_valin_set(number v) {
    this->numberobj_22_value_set(v);
}

void numberobj_22_format_set(number v) {
    this->numberobj_22_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_23_valin_set(number v) {
    this->numberobj_23_value_set(v);
}

void numberobj_23_format_set(number v) {
    this->numberobj_23_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void inport_09_value_bang_bang() {
    this->inport_09_out_bang_bang();
}

void inport_09_value_number_set(number v) {
    this->inport_09_out_number_set(v);
}

void inport_09_value_list_set(const list& v) {
    this->inport_09_out_list_set(v);
}

void numbertilde_01_value_set(number v) {
    this->numberobj_06_value_set(v);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

Index getNumInputChannels() const {
    return 0;
}

Index getNumOutputChannels() const {
    return 16;
}

void allocateDataRefs() {
    this->groove_01_buffer = this->groove_01_buffer->allocateIfNeeded();
    this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();

    if (this->playback->hasRequestedSize()) {
        if (this->playback->wantsFill())
            this->zeroDataRef(this->playback);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->data_02_buffer = this->data_02_buffer->allocateIfNeeded();

    if (this->b_audio_wav->hasRequestedSize()) {
        if (this->b_audio_wav->wantsFill())
            this->zeroDataRef(this->b_audio_wav);

        this->getEngine()->sendDataRefUpdated(1);
    }
}

void initializeObjects() {
    this->gaintilde_01_init();
    this->gaintilde_02_init();
    this->gaintilde_03_init();
    this->gaintilde_04_init();
    this->numberobj_01_init();
    this->message_01_init();
    this->gaintilde_05_init();
    this->gaintilde_06_init();
    this->gaintilde_07_init();
    this->gaintilde_08_init();
    this->gaintilde_09_init();
    this->numberobj_02_init();
    this->data_01_init();
    this->gaintilde_10_init();
    this->gaintilde_11_init();
    this->numberobj_03_init();
    this->gaintilde_12_init();
    this->gaintilde_13_init();
    this->numberobj_04_init();
    this->gaintilde_14_init();
    this->numberobj_05_init();
    this->gaintilde_15_init();
    this->gaintilde_16_init();
    this->numbertilde_01_init();
    this->numberobj_06_init();
    this->numberobj_07_init();
    this->message_02_init();
    this->data_02_init();
    this->numberobj_08_init();
    this->numberobj_09_init();
    this->numberobj_10_init();
    this->numberobj_11_init();
    this->numberobj_12_init();
    this->numberobj_13_init();
    this->numberobj_14_init();
    this->numberobj_15_init();
    this->numberobj_16_init();
    this->numberobj_17_init();
    this->numberobj_18_init();
    this->numberobj_19_init();
    this->numberobj_20_init();
    this->numberobj_21_init();
    this->numberobj_22_init();
    this->numberobj_23_init();
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime());
    this->getEngine()->scheduleClockEvent(this, -1735137014, 0 + this->_currentTime);;
    this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    this->processParamInitEvents();
}

void outport_02_input_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("loopeando"), TAG(""), v, this->_currentTime);
}

void groove_01_loop_set(number v) {
    this->groove_01_loop = v;
}

void numberobj_05_output_set(number v) {
    this->outport_02_input_number_set(v);
    this->groove_01_loop_set(v);
}

void numberobj_05_value_bang() {
    number v = this->numberobj_05_value;
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-103"), localvalue, this->_currentTime);
    this->numberobj_05_output_set(localvalue);
}

void numberobj_01_output_set(number ) {}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-3"), localvalue, this->_currentTime);
    this->numberobj_01_output_set(localvalue);
}

void message_01_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_01_value_set(converted);
    }
}

void message_01_trigger_bang() {
    this->message_01_out_set(this->message_01_set);
}

void outport_01_input_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("channels"), TAG(""), v, this->_currentTime);
}

void message_01_set_set(const list& v) {
    this->message_01_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-15"), v, this->_currentTime);
}

void numberobj_03_output_set(number v) {
    this->outport_01_input_number_set(v);

    {
        list converted = {v};
        this->message_01_set_set(converted);
    }

    this->message_01_trigger_bang();
}

void numberobj_03_value_bang() {
    number v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-4"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

void delay_01_stop_bang() {
    this->getEngine()->flushClockEvents(this, -217479832, false);;
}

void delay_01_input_bang() {
    if ((bool)(!(bool)(this->delay_01_delayall)))
        this->delay_01_stop_bang();

    this->getEngine()->scheduleClockEvent(this, -217479832, this->delay_01_time + this->_currentTime);;
}

void button_01_output_bang() {
    this->numberobj_03_value_bang();
    this->delay_01_input_bang();
}

void button_01_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-118"), this->_currentTime);;
    this->button_01_output_bang();
}

void inport_01_out_bang_bang() {
    this->button_01_bangval_bang();
}

void inport_01_out_number_set(number v) {
    RNBO_UNUSED(v);
    this->button_01_bangval_bang();
}

void inport_01_out_list_set(const list& v) {
    RNBO_UNUSED(v);
    this->button_01_bangval_bang();
}

void gaintilde_01_outval_set(number ) {}

void gaintilde_01_value_set(number v) {
    this->gaintilde_01_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-48"), v, this->_currentTime);
    this->gaintilde_01_outval_set(value);
}

void groove_01_rate_bang_bang() {
    this->groove_01_changeIncomingInSamples = this->sampleOffsetIntoNextAudioBuffer + 1;
    this->groove_01_incomingChange = 1;
}

void button_02_output_bang() {
    this->groove_01_rate_bang_bang();
}

void button_02_bangval_bang() {
    this->getEngine()->sendBangMessage(TAG("bangout"), TAG("button_obj-17"), this->_currentTime);;
    this->button_02_output_bang();
}

void delay_04_stop_bang() {
    this->getEngine()->flushClockEvents(this, 922084457, false);;
}

void delay_04_input_bang() {
    if ((bool)(!(bool)(this->delay_04_delayall)))
        this->delay_04_stop_bang();

    this->getEngine()->scheduleClockEvent(this, 922084457, this->delay_04_time + this->_currentTime);;
}

void delay_03_stop_bang() {
    this->getEngine()->flushClockEvents(this, 2061648746, false);;
}

void delay_03_input_bang() {
    if ((bool)(!(bool)(this->delay_03_delayall)))
        this->delay_03_stop_bang();

    this->getEngine()->scheduleClockEvent(this, 2061648746, this->delay_03_time + this->_currentTime);;
}

void delay_02_stop_bang() {
    this->getEngine()->flushClockEvents(this, -1093754261, false);;
}

void delay_02_input_bang() {
    if ((bool)(!(bool)(this->delay_02_delayall)))
        this->delay_02_stop_bang();

    this->getEngine()->scheduleClockEvent(this, -1093754261, this->delay_02_time + this->_currentTime);;
}

void loadbang_01_output_bang() {
    this->delay_04_input_bang();
    this->delay_03_input_bang();
    this->delay_02_input_bang();
}

void gaintilde_02_outval_set(number ) {}

void gaintilde_02_value_set(number v) {
    this->gaintilde_02_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-36"), v, this->_currentTime);
    this->gaintilde_02_outval_set(value);
}

void gaintilde_03_outval_set(number ) {}

void gaintilde_03_value_set(number v) {
    this->gaintilde_03_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-38"), v, this->_currentTime);
    this->gaintilde_03_outval_set(value);
}

void data_02_srout_set(number ) {}

void data_02_chanout_set(number ) {}

void data_02_sizeout_set(number v) {
    this->data_02_sizeout = v;
}

void data_02_info_bang() {
    this->data_02_report();
}

void gaintilde_04_outval_set(number ) {}

void gaintilde_04_value_set(number v) {
    this->gaintilde_04_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-37"), v, this->_currentTime);
    this->gaintilde_04_outval_set(value);
}

void gaintilde_05_outval_set(number ) {}

void gaintilde_05_value_set(number v) {
    this->gaintilde_05_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-42"), v, this->_currentTime);
    this->gaintilde_05_outval_set(value);
}

void gaintilde_06_outval_set(number ) {}

void gaintilde_06_value_set(number v) {
    this->gaintilde_06_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-41"), v, this->_currentTime);
    this->gaintilde_06_outval_set(value);
}

void gaintilde_07_outval_set(number ) {}

void gaintilde_07_value_set(number v) {
    this->gaintilde_07_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-40"), v, this->_currentTime);
    this->gaintilde_07_outval_set(value);
}

void gaintilde_08_outval_set(number ) {}

void gaintilde_08_value_set(number v) {
    this->gaintilde_08_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-39"), v, this->_currentTime);
    this->gaintilde_08_outval_set(value);
}

void numberobj_05_value_set(number v) {
    this->numberobj_05_value_setter(v);
    v = this->numberobj_05_value;
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-103"), localvalue, this->_currentTime);
    this->numberobj_05_output_set(localvalue);
}

void toggle_01_output_set(number v) {
    this->numberobj_05_value_set(v);
}

void toggle_01_value_number_set(number v) {
    this->toggle_01_value_number_setter(v);
    v = this->toggle_01_value_number;
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("toggle_obj-14"), v, this->_currentTime);
    this->toggle_01_output_set(v);
}

void toggle_01_value_bang_bang() {
    number val = (this->toggle_01_value_number == 1 ? 0 : 1);
    this->toggle_01_value_number_set(val);
}

void gaintilde_09_outval_set(number ) {}

void gaintilde_09_value_set(number v) {
    this->gaintilde_09_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-51"), v, this->_currentTime);
    this->gaintilde_09_outval_set(value);
}

void outport_04_input_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("durSeg"), TAG(""), v, this->_currentTime);
}

void numberobj_07_output_set(number v) {
    this->outport_04_input_number_set(v);
}

void numberobj_07_value_set(number v) {
    this->numberobj_07_value_setter(v);
    v = this->numberobj_07_value;
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-159"), localvalue, this->_currentTime);
    this->numberobj_07_output_set(localvalue);
}

void expr_01_out1_set(number v) {
    this->expr_01_out1 = v;
    this->numberobj_07_value_set(this->expr_01_out1);
}

void expr_01_in1_set(number in1) {
    this->expr_01_in1 = in1;

    this->expr_01_out1_set(
        (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
    );//#map:/_obj-157:1
}

void numberobj_02_output_set(number v) {
    this->expr_01_in1_set(v);
}

void numberobj_02_value_set(number v) {
    this->numberobj_02_value_setter(v);
    v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-6"), localvalue, this->_currentTime);
    this->numberobj_02_output_set(localvalue);
}

void gaintilde_10_outval_set(number ) {}

void gaintilde_10_value_set(number v) {
    this->gaintilde_10_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-50"), v, this->_currentTime);
    this->gaintilde_10_outval_set(value);
}

void gaintilde_11_outval_set(number ) {}

void gaintilde_11_value_set(number v) {
    this->gaintilde_11_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-49"), v, this->_currentTime);
    this->gaintilde_11_outval_set(value);
}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-4"), localvalue, this->_currentTime);
    this->numberobj_03_output_set(localvalue);
}

void gaintilde_12_outval_set(number ) {}

void gaintilde_12_value_set(number v) {
    this->gaintilde_12_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-47"), v, this->_currentTime);
    this->gaintilde_12_outval_set(value);
}

void gaintilde_13_outval_set(number ) {}

void gaintilde_13_value_set(number v) {
    this->gaintilde_13_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-46"), v, this->_currentTime);
    this->gaintilde_13_outval_set(value);
}

void numberobj_04_output_set(number ) {}

void numberobj_04_value_set(number v) {
    this->numberobj_04_value_setter(v);
    v = this->numberobj_04_value;
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-113"), localvalue, this->_currentTime);
    this->numberobj_04_output_set(localvalue);
}

void gaintilde_14_outval_set(number ) {}

void gaintilde_14_value_set(number v) {
    this->gaintilde_14_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-45"), v, this->_currentTime);
    this->gaintilde_14_outval_set(value);
}

void gaintilde_15_outval_set(number ) {}

void gaintilde_15_value_set(number v) {
    this->gaintilde_15_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-44"), v, this->_currentTime);
    this->gaintilde_15_outval_set(value);
}

void gaintilde_16_outval_set(number ) {}

void gaintilde_16_value_set(number v) {
    this->gaintilde_16_value = v;
    number value;
    value = this->scale(v, 0, 157, 0, 158 - 1, 1);
    this->getEngine()->sendNumMessage(TAG("valout"), TAG("gain~_obj-43"), v, this->_currentTime);
    this->gaintilde_16_outval_set(value);
}

void outport_03_input_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("seg"), TAG(""), v, this->_currentTime);
}

void numberobj_06_output_set(number v) {
    this->outport_03_input_number_set(v);
}

void numberobj_06_value_set(number v) {
    this->numberobj_06_value_setter(v);
    v = this->numberobj_06_value;
    number localvalue = v;

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-152"), localvalue, this->_currentTime);
    this->numberobj_06_output_set(localvalue);
}

void outport_12_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen8"), TAG(""), v, this->_currentTime);
}

void scale_15_out_set(const list& v) {
    this->scale_15_out = jsCreateListCopy(v);
    this->outport_12_input_list_set(v);
}

void scale_15_input_set(const list& v) {
    this->scale_15_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_15_inlow,
            this->scale_15_inhigh,
            this->scale_15_outlow,
            this->scale_15_outhigh,
            this->scale_15_power
        ));
    }

    this->scale_15_out_set(tmp);
}

void gaintilde_08_input_number_set(number v) {
    this->gaintilde_08_input_number = v;

    this->gaintilde_08_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_22_output_set(number v) {
    {
        list converted = {v};
        this->scale_15_input_set(converted);
    }

    this->gaintilde_08_input_number_set(v);
}

void numberobj_22_value_set(number v) {
    this->numberobj_22_value_setter(v);
    v = this->numberobj_22_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-153"), localvalue, this->_currentTime);
    this->numberobj_22_output_set(localvalue);
}

void scale_16_out_set(const list& v) {
    this->scale_16_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_22_value_set(converted);
    }
}

void scale_16_input_set(const list& v) {
    this->scale_16_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_16_inlow,
            this->scale_16_inhigh,
            this->scale_16_outlow,
            this->scale_16_outhigh,
            this->scale_16_power
        ));
    }

    this->scale_16_out_set(tmp);
}

void numberobj_23_output_set(number v) {
    {
        list converted = {v};
        this->scale_16_input_set(converted);
    }
}

void numberobj_23_value_set(number v) {
    this->numberobj_23_value_setter(v);
    v = this->numberobj_23_value;
    number localvalue = v;

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-95"), localvalue, this->_currentTime);
    this->numberobj_23_output_set(localvalue);
}

void outport_11_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen7"), TAG(""), v, this->_currentTime);
}

void scale_13_out_set(const list& v) {
    this->scale_13_out = jsCreateListCopy(v);
    this->outport_11_input_list_set(v);
}

void scale_13_input_set(const list& v) {
    this->scale_13_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_13_inlow,
            this->scale_13_inhigh,
            this->scale_13_outlow,
            this->scale_13_outhigh,
            this->scale_13_power
        ));
    }

    this->scale_13_out_set(tmp);
}

void gaintilde_07_input_number_set(number v) {
    this->gaintilde_07_input_number = v;

    this->gaintilde_07_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_20_output_set(number v) {
    {
        list converted = {v};
        this->scale_13_input_set(converted);
    }

    this->gaintilde_07_input_number_set(v);
}

void numberobj_20_value_set(number v) {
    this->numberobj_20_value_setter(v);
    v = this->numberobj_20_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-151"), localvalue, this->_currentTime);
    this->numberobj_20_output_set(localvalue);
}

void scale_14_out_set(const list& v) {
    this->scale_14_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_20_value_set(converted);
    }
}

void scale_14_input_set(const list& v) {
    this->scale_14_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_14_inlow,
            this->scale_14_inhigh,
            this->scale_14_outlow,
            this->scale_14_outhigh,
            this->scale_14_power
        ));
    }

    this->scale_14_out_set(tmp);
}

void numberobj_21_output_set(number v) {
    {
        list converted = {v};
        this->scale_14_input_set(converted);
    }
}

void numberobj_21_value_set(number v) {
    this->numberobj_21_value_setter(v);
    v = this->numberobj_21_value;
    number localvalue = v;

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-99"), localvalue, this->_currentTime);
    this->numberobj_21_output_set(localvalue);
}

void outport_10_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen6"), TAG(""), v, this->_currentTime);
}

void scale_11_out_set(const list& v) {
    this->scale_11_out = jsCreateListCopy(v);
    this->outport_10_input_list_set(v);
}

void scale_11_input_set(const list& v) {
    this->scale_11_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_11_inlow,
            this->scale_11_inhigh,
            this->scale_11_outlow,
            this->scale_11_outhigh,
            this->scale_11_power
        ));
    }

    this->scale_11_out_set(tmp);
}

void gaintilde_06_input_number_set(number v) {
    this->gaintilde_06_input_number = v;

    this->gaintilde_06_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_18_output_set(number v) {
    {
        list converted = {v};
        this->scale_11_input_set(converted);
    }

    this->gaintilde_06_input_number_set(v);
}

void numberobj_18_value_set(number v) {
    this->numberobj_18_value_setter(v);
    v = this->numberobj_18_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-149"), localvalue, this->_currentTime);
    this->numberobj_18_output_set(localvalue);
}

void scale_12_out_set(const list& v) {
    this->scale_12_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_18_value_set(converted);
    }
}

void scale_12_input_set(const list& v) {
    this->scale_12_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_12_inlow,
            this->scale_12_inhigh,
            this->scale_12_outlow,
            this->scale_12_outhigh,
            this->scale_12_power
        ));
    }

    this->scale_12_out_set(tmp);
}

void numberobj_19_output_set(number v) {
    {
        list converted = {v};
        this->scale_12_input_set(converted);
    }
}

void numberobj_19_value_set(number v) {
    this->numberobj_19_value_setter(v);
    v = this->numberobj_19_value;
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-102"), localvalue, this->_currentTime);
    this->numberobj_19_output_set(localvalue);
}

void outport_09_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen5"), TAG(""), v, this->_currentTime);
}

void scale_09_out_set(const list& v) {
    this->scale_09_out = jsCreateListCopy(v);
    this->outport_09_input_list_set(v);
}

void scale_09_input_set(const list& v) {
    this->scale_09_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_09_inlow,
            this->scale_09_inhigh,
            this->scale_09_outlow,
            this->scale_09_outhigh,
            this->scale_09_power
        ));
    }

    this->scale_09_out_set(tmp);
}

void gaintilde_05_input_number_set(number v) {
    this->gaintilde_05_input_number = v;

    this->gaintilde_05_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_16_output_set(number v) {
    {
        list converted = {v};
        this->scale_09_input_set(converted);
    }

    this->gaintilde_05_input_number_set(v);
}

void numberobj_16_value_set(number v) {
    this->numberobj_16_value_setter(v);
    v = this->numberobj_16_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-148"), localvalue, this->_currentTime);
    this->numberobj_16_output_set(localvalue);
}

void scale_10_out_set(const list& v) {
    this->scale_10_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_16_value_set(converted);
    }
}

void scale_10_input_set(const list& v) {
    this->scale_10_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_10_inlow,
            this->scale_10_inhigh,
            this->scale_10_outlow,
            this->scale_10_outhigh,
            this->scale_10_power
        ));
    }

    this->scale_10_out_set(tmp);
}

void numberobj_17_output_set(number v) {
    {
        list converted = {v};
        this->scale_10_input_set(converted);
    }
}

void numberobj_17_value_set(number v) {
    this->numberobj_17_value_setter(v);
    v = this->numberobj_17_value;
    number localvalue = v;

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-107"), localvalue, this->_currentTime);
    this->numberobj_17_output_set(localvalue);
}

void outport_08_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen4"), TAG(""), v, this->_currentTime);
}

void scale_07_out_set(const list& v) {
    this->scale_07_out = jsCreateListCopy(v);
    this->outport_08_input_list_set(v);
}

void scale_07_input_set(const list& v) {
    this->scale_07_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_07_inlow,
            this->scale_07_inhigh,
            this->scale_07_outlow,
            this->scale_07_outhigh,
            this->scale_07_power
        ));
    }

    this->scale_07_out_set(tmp);
}

void gaintilde_04_input_number_set(number v) {
    this->gaintilde_04_input_number = v;

    this->gaintilde_04_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_14_output_set(number v) {
    {
        list converted = {v};
        this->scale_07_input_set(converted);
    }

    this->gaintilde_04_input_number_set(v);
}

void numberobj_14_value_set(number v) {
    this->numberobj_14_value_setter(v);
    v = this->numberobj_14_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_14_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-146"), localvalue, this->_currentTime);
    this->numberobj_14_output_set(localvalue);
}

void scale_08_out_set(const list& v) {
    this->scale_08_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_14_value_set(converted);
    }
}

void scale_08_input_set(const list& v) {
    this->scale_08_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_08_inlow,
            this->scale_08_inhigh,
            this->scale_08_outlow,
            this->scale_08_outhigh,
            this->scale_08_power
        ));
    }

    this->scale_08_out_set(tmp);
}

void numberobj_15_output_set(number v) {
    {
        list converted = {v};
        this->scale_08_input_set(converted);
    }
}

void numberobj_15_value_set(number v) {
    this->numberobj_15_value_setter(v);
    v = this->numberobj_15_value;
    number localvalue = v;

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-89"), localvalue, this->_currentTime);
    this->numberobj_15_output_set(localvalue);
}

void outport_07_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen3"), TAG(""), v, this->_currentTime);
}

void scale_05_out_set(const list& v) {
    this->scale_05_out = jsCreateListCopy(v);
    this->outport_07_input_list_set(v);
}

void scale_05_input_set(const list& v) {
    this->scale_05_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_05_inlow,
            this->scale_05_inhigh,
            this->scale_05_outlow,
            this->scale_05_outhigh,
            this->scale_05_power
        ));
    }

    this->scale_05_out_set(tmp);
}

void gaintilde_03_input_number_set(number v) {
    this->gaintilde_03_input_number = v;

    this->gaintilde_03_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_12_output_set(number v) {
    {
        list converted = {v};
        this->scale_05_input_set(converted);
    }

    this->gaintilde_03_input_number_set(v);
}

void numberobj_12_value_set(number v) {
    this->numberobj_12_value_setter(v);
    v = this->numberobj_12_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_12_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-144"), localvalue, this->_currentTime);
    this->numberobj_12_output_set(localvalue);
}

void scale_06_out_set(const list& v) {
    this->scale_06_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_12_value_set(converted);
    }
}

void scale_06_input_set(const list& v) {
    this->scale_06_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_06_inlow,
            this->scale_06_inhigh,
            this->scale_06_outlow,
            this->scale_06_outhigh,
            this->scale_06_power
        ));
    }

    this->scale_06_out_set(tmp);
}

void numberobj_13_output_set(number v) {
    {
        list converted = {v};
        this->scale_06_input_set(converted);
    }
}

void numberobj_13_value_set(number v) {
    this->numberobj_13_value_setter(v);
    v = this->numberobj_13_value;
    number localvalue = v;

    if (this->numberobj_13_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-92"), localvalue, this->_currentTime);
    this->numberobj_13_output_set(localvalue);
}

void outport_06_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen2"), TAG(""), v, this->_currentTime);
}

void scale_03_out_set(const list& v) {
    this->scale_03_out = jsCreateListCopy(v);
    this->outport_06_input_list_set(v);
}

void scale_03_input_set(const list& v) {
    this->scale_03_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_03_inlow,
            this->scale_03_inhigh,
            this->scale_03_outlow,
            this->scale_03_outhigh,
            this->scale_03_power
        ));
    }

    this->scale_03_out_set(tmp);
}

void gaintilde_02_input_number_set(number v) {
    this->gaintilde_02_input_number = v;

    this->gaintilde_02_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_10_output_set(number v) {
    {
        list converted = {v};
        this->scale_03_input_set(converted);
    }

    this->gaintilde_02_input_number_set(v);
}

void numberobj_10_value_set(number v) {
    this->numberobj_10_value_setter(v);
    v = this->numberobj_10_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-143"), localvalue, this->_currentTime);
    this->numberobj_10_output_set(localvalue);
}

void scale_04_out_set(const list& v) {
    this->scale_04_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_10_value_set(converted);
    }
}

void scale_04_input_set(const list& v) {
    this->scale_04_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_04_inlow,
            this->scale_04_inhigh,
            this->scale_04_outlow,
            this->scale_04_outhigh,
            this->scale_04_power
        ));
    }

    this->scale_04_out_set(tmp);
}

void numberobj_11_output_set(number v) {
    {
        list converted = {v};
        this->scale_04_input_set(converted);
    }
}

void numberobj_11_value_set(number v) {
    this->numberobj_11_value_setter(v);
    v = this->numberobj_11_value;
    number localvalue = v;

    if (this->numberobj_11_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-85"), localvalue, this->_currentTime);
    this->numberobj_11_output_set(localvalue);
}

void outport_05_input_list_set(const list& v) {
    this->getEngine()->sendListMessage(TAG("volumen1"), TAG(""), v, this->_currentTime);
}

void scale_02_out_set(const list& v) {
    this->scale_02_out = jsCreateListCopy(v);
    this->outport_05_input_list_set(v);
}

void scale_02_input_set(const list& v) {
    this->scale_02_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_02_inlow,
            this->scale_02_inhigh,
            this->scale_02_outlow,
            this->scale_02_outhigh,
            this->scale_02_power
        ));
    }

    this->scale_02_out_set(tmp);
}

void gaintilde_01_input_number_set(number v) {
    this->gaintilde_01_input_number = v;

    this->gaintilde_01_value_set(
        this->scale((v > 158 - 1 ? 158 - 1 : (v < 0 ? 0 : v)), 0, 158 - 1, 0, 157, 1)
    );
}

void numberobj_09_output_set(number v) {
    {
        list converted = {v};
        this->scale_02_input_set(converted);
    }

    this->gaintilde_01_input_number_set(v);
}

void numberobj_09_value_set(number v) {
    this->numberobj_09_value_setter(v);
    v = this->numberobj_09_value;
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-136"), localvalue, this->_currentTime);
    this->numberobj_09_output_set(localvalue);
}

void scale_01_out_set(const list& v) {
    this->scale_01_out = jsCreateListCopy(v);

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_09_value_set(converted);
    }
}

void scale_01_input_set(const list& v) {
    this->scale_01_input = jsCreateListCopy(v);
    list tmp = {};

    for (Index i = 0; i < v->length; i++) {
        tmp->push(this->scale(
            v[(Index)i],
            this->scale_01_inlow,
            this->scale_01_inhigh,
            this->scale_01_outlow,
            this->scale_01_outhigh,
            this->scale_01_power
        ));
    }

    this->scale_01_out_set(tmp);
}

void numberobj_08_output_set(number v) {
    {
        list converted = {v};
        this->scale_01_input_set(converted);
    }
}

void numberobj_08_value_set(number v) {
    this->numberobj_08_value_setter(v);
    v = this->numberobj_08_value;
    number localvalue = v;

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-60"), localvalue, this->_currentTime);
    this->numberobj_08_output_set(localvalue);
}

void message_02_out_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_23_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_21_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_19_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_17_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_15_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_13_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_11_value_set(converted);
    }

    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_08_value_set(converted);
    }
}

void message_02_trigger_bang() {
    this->message_02_out_set(this->message_02_set);
}

void delay_05_stop_bang() {
    this->getEngine()->flushClockEvents(this, -1357044121, false);;
}

void delay_05_input_bang() {
    if ((bool)(!(bool)(this->delay_05_delayall)))
        this->delay_05_stop_bang();

    this->getEngine()->scheduleClockEvent(this, -1357044121, this->delay_05_time + this->_currentTime);;
}

void loadbang_02_output_bang() {
    this->delay_05_input_bang();
}

void message_02_set_set(const list& v) {
    this->message_02_set = jsCreateListCopy(v);
    this->getEngine()->sendListMessage(TAG("listout"), TAG("message_obj-130"), v, this->_currentTime);
}

void numberobj_08_value_bang() {
    number v = this->numberobj_08_value;
    number localvalue = v;

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-60"), localvalue, this->_currentTime);
    this->numberobj_08_output_set(localvalue);
}

void inport_02_out_bang_bang() {
    this->numberobj_08_value_bang();
}

void inport_02_out_number_set(number v) {
    this->numberobj_08_value_set(v);
}

void inport_02_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_08_value_set(converted);
    }
}

void numberobj_11_value_bang() {
    number v = this->numberobj_11_value;
    number localvalue = v;

    if (this->numberobj_11_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-85"), localvalue, this->_currentTime);
    this->numberobj_11_output_set(localvalue);
}

void inport_03_out_bang_bang() {
    this->numberobj_11_value_bang();
}

void inport_03_out_number_set(number v) {
    this->numberobj_11_value_set(v);
}

void inport_03_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_11_value_set(converted);
    }
}

void numberobj_13_value_bang() {
    number v = this->numberobj_13_value;
    number localvalue = v;

    if (this->numberobj_13_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-92"), localvalue, this->_currentTime);
    this->numberobj_13_output_set(localvalue);
}

void inport_04_out_bang_bang() {
    this->numberobj_13_value_bang();
}

void inport_04_out_number_set(number v) {
    this->numberobj_13_value_set(v);
}

void inport_04_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_13_value_set(converted);
    }
}

void numberobj_15_value_bang() {
    number v = this->numberobj_15_value;
    number localvalue = v;

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-89"), localvalue, this->_currentTime);
    this->numberobj_15_output_set(localvalue);
}

void inport_05_out_bang_bang() {
    this->numberobj_15_value_bang();
}

void inport_05_out_number_set(number v) {
    this->numberobj_15_value_set(v);
}

void inport_05_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_15_value_set(converted);
    }
}

void numberobj_17_value_bang() {
    number v = this->numberobj_17_value;
    number localvalue = v;

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-107"), localvalue, this->_currentTime);
    this->numberobj_17_output_set(localvalue);
}

void inport_06_out_bang_bang() {
    this->numberobj_17_value_bang();
}

void inport_06_out_number_set(number v) {
    this->numberobj_17_value_set(v);
}

void inport_06_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_17_value_set(converted);
    }
}

void numberobj_19_value_bang() {
    number v = this->numberobj_19_value;
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-102"), localvalue, this->_currentTime);
    this->numberobj_19_output_set(localvalue);
}

void inport_07_out_bang_bang() {
    this->numberobj_19_value_bang();
}

void inport_07_out_number_set(number v) {
    this->numberobj_19_value_set(v);
}

void inport_07_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_19_value_set(converted);
    }
}

void numberobj_21_value_bang() {
    number v = this->numberobj_21_value;
    number localvalue = v;

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-99"), localvalue, this->_currentTime);
    this->numberobj_21_output_set(localvalue);
}

void inport_08_out_bang_bang() {
    this->numberobj_21_value_bang();
}

void inport_08_out_number_set(number v) {
    this->numberobj_21_value_set(v);
}

void inport_08_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_21_value_set(converted);
    }
}

void numberobj_23_value_bang() {
    number v = this->numberobj_23_value;
    number localvalue = v;

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->getEngine()->sendNumMessage(TAG("valout"), TAG("number_obj-95"), localvalue, this->_currentTime);
    this->numberobj_23_output_set(localvalue);
}

void inport_09_out_bang_bang() {
    this->numberobj_23_value_bang();
}

void inport_09_out_number_set(number v) {
    this->numberobj_23_value_set(v);
}

void inport_09_out_list_set(const list& v) {
    {
        number converted = (v->length > 0 ? v[0] : 0);
        this->numberobj_23_value_set(converted);
    }
}

void groove_01_perform(
    number rate_auto,
    number begin,
    number end,
    SampleValue * out1,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(out1);
    RNBO_UNUSED(end);
    RNBO_UNUSED(begin);
    RNBO_UNUSED(rate_auto);
    auto __groove_01_crossfade = this->groove_01_crossfade;
    auto __groove_01_loop = this->groove_01_loop;
    auto __groove_01_playStatus = this->groove_01_playStatus;
    auto __groove_01_readIndex = this->groove_01_readIndex;
    auto __groove_01_incomingChange = this->groove_01_incomingChange;
    auto __groove_01_changeIncomingInSamples = this->groove_01_changeIncomingInSamples;
    auto __groove_01_buffer = this->groove_01_buffer;
    SampleArray<1> out = {out1};
    SampleIndex bufferLength = (SampleIndex)(__groove_01_buffer->getSize());
    Index i = 0;

    if (bufferLength > 1) {
        auto effectiveChannels = this->minimum(__groove_01_buffer->getChannels(), 1);
        number srMult = 0.001 * __groove_01_buffer->getSampleRate();
        number srInv = (number)1 / this->samplerate();
        number rateMult = __groove_01_buffer->getSampleRate() * srInv;

        for (; i < n; i++) {
            Index channel = 0;
            number offset = 0;
            number loopMin = 0 * srMult;
            loopMin = (loopMin > bufferLength - 1 ? bufferLength - 1 : (loopMin < 0 ? 0 : loopMin));
            number loopMax = bufferLength;
            loopMax = (loopMax > bufferLength ? bufferLength : (loopMax < 0 ? 0 : loopMax));

            if (loopMin >= loopMax) {
                offset = loopMax;
                loopMax = bufferLength;
                loopMin -= offset;
            }

            number loopLength = loopMax - loopMin;
            number currentRate = 1 * rateMult;
            number currentSync = 0;

            if (__groove_01_changeIncomingInSamples > 0) {
                __groove_01_changeIncomingInSamples--;

                if (__groove_01_changeIncomingInSamples <= 0) {
                    if (__groove_01_incomingChange == 1) {
                        if (currentRate < 0) {
                            __groove_01_readIndex = loopMax - 1;
                        } else {
                            __groove_01_readIndex = loopMin;
                        }

                        __groove_01_playStatus = 1;
                    } else if (__groove_01_incomingChange == 0) {
                        __groove_01_playStatus = 0;
                    }

                    __groove_01_incomingChange = 2;
                }
            }

            if (loopLength > 0) {
                if (currentRate != 0) {
                    if (__groove_01_playStatus == 1) {
                        if ((bool)(__groove_01_loop)) {
                            while (__groove_01_readIndex < loopMin) {
                                __groove_01_readIndex += loopLength;
                            }

                            while (__groove_01_readIndex >= loopMax) {
                                __groove_01_readIndex -= loopLength;
                            }
                        } else if (__groove_01_readIndex >= loopMax || __groove_01_readIndex < loopMin) {
                            __groove_01_playStatus = 0;
                            break;
                        }

                        for (; channel < effectiveChannels; channel++) {
                            number outSample = (currentRate == 1 ? this->groove_01_getSample((Index)(channel), trunc(__groove_01_readIndex), offset, bufferLength) : this->groove_01_interpolatedSample(
                                (Index)(channel),
                                __groove_01_readIndex,
                                loopMax,
                                loopLength,
                                offset,
                                bufferLength
                            ));

                            if (__groove_01_crossfade > 0) {
                                out[(Index)channel][(Index)i] = this->groove_01_crossfadedSample(
                                    outSample,
                                    __groove_01_readIndex,
                                    (Index)(channel),
                                    currentRate,
                                    loopMin,
                                    loopMax,
                                    loopLength,
                                    offset,
                                    bufferLength
                                );
                            } else {
                                out[(Index)channel][(Index)i] = outSample;
                            }
                        }

                        {
                            currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                        }

                        __groove_01_readIndex += currentRate;
                    }
                } else {
                    if (__groove_01_playStatus == 1) {
                        currentSync = this->groove_01_calcSync(__groove_01_readIndex, offset, loopMin, loopLength, bufferLength, srInv);
                    }
                }
            }

            {
                sync[(Index)i] = currentSync;
            }

            for (; channel < 1; channel++) {
                if (__groove_01_playStatus <= 0)
                    sync[(Index)i] = 0;

                out[(Index)channel][(Index)i] = 0;
            }
        }
    }

    for (; i < n; i++) {
        if (__groove_01_playStatus <= 0)
            sync[(Index)i] = 0;

        for (number channel = 0; channel < 1; channel++) {
            out[(Index)channel][(Index)i] = 0;
        }
    }

    this->groove_01_changeIncomingInSamples = __groove_01_changeIncomingInSamples;
    this->groove_01_incomingChange = __groove_01_incomingChange;
    this->groove_01_readIndex = __groove_01_readIndex;
    this->groove_01_playStatus = __groove_01_playStatus;
}

void gaintilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_01_interp = this->gaintilde_01_interp;
    auto __gaintilde_01_loginc = this->gaintilde_01_loginc;
    auto __gaintilde_01_zval = this->gaintilde_01_zval;
    auto __gaintilde_01_value = this->gaintilde_01_value;
    number mult = (__gaintilde_01_value <= 0 ? 0. : __gaintilde_01_zval * rnbo_exp(__gaintilde_01_value * __gaintilde_01_loginc));
    auto iv = this->mstosamps(__gaintilde_01_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_01_ramp_next(mult, iv, iv);
    }
}

void gaintilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_02_interp = this->gaintilde_02_interp;
    auto __gaintilde_02_loginc = this->gaintilde_02_loginc;
    auto __gaintilde_02_zval = this->gaintilde_02_zval;
    auto __gaintilde_02_value = this->gaintilde_02_value;
    number mult = (__gaintilde_02_value <= 0 ? 0. : __gaintilde_02_zval * rnbo_exp(__gaintilde_02_value * __gaintilde_02_loginc));
    auto iv = this->mstosamps(__gaintilde_02_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_02_ramp_next(mult, iv, iv);
    }
}

void gaintilde_03_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_03_interp = this->gaintilde_03_interp;
    auto __gaintilde_03_loginc = this->gaintilde_03_loginc;
    auto __gaintilde_03_zval = this->gaintilde_03_zval;
    auto __gaintilde_03_value = this->gaintilde_03_value;
    number mult = (__gaintilde_03_value <= 0 ? 0. : __gaintilde_03_zval * rnbo_exp(__gaintilde_03_value * __gaintilde_03_loginc));
    auto iv = this->mstosamps(__gaintilde_03_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_03_ramp_next(mult, iv, iv);
    }
}

void gaintilde_04_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_04_interp = this->gaintilde_04_interp;
    auto __gaintilde_04_loginc = this->gaintilde_04_loginc;
    auto __gaintilde_04_zval = this->gaintilde_04_zval;
    auto __gaintilde_04_value = this->gaintilde_04_value;
    number mult = (__gaintilde_04_value <= 0 ? 0. : __gaintilde_04_zval * rnbo_exp(__gaintilde_04_value * __gaintilde_04_loginc));
    auto iv = this->mstosamps(__gaintilde_04_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_04_ramp_next(mult, iv, iv);
    }
}

void gaintilde_05_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_05_interp = this->gaintilde_05_interp;
    auto __gaintilde_05_loginc = this->gaintilde_05_loginc;
    auto __gaintilde_05_zval = this->gaintilde_05_zval;
    auto __gaintilde_05_value = this->gaintilde_05_value;
    number mult = (__gaintilde_05_value <= 0 ? 0. : __gaintilde_05_zval * rnbo_exp(__gaintilde_05_value * __gaintilde_05_loginc));
    auto iv = this->mstosamps(__gaintilde_05_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_05_ramp_next(mult, iv, iv);
    }
}

void gaintilde_06_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_06_interp = this->gaintilde_06_interp;
    auto __gaintilde_06_loginc = this->gaintilde_06_loginc;
    auto __gaintilde_06_zval = this->gaintilde_06_zval;
    auto __gaintilde_06_value = this->gaintilde_06_value;
    number mult = (__gaintilde_06_value <= 0 ? 0. : __gaintilde_06_zval * rnbo_exp(__gaintilde_06_value * __gaintilde_06_loginc));
    auto iv = this->mstosamps(__gaintilde_06_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_06_ramp_next(mult, iv, iv);
    }
}

void gaintilde_07_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_07_interp = this->gaintilde_07_interp;
    auto __gaintilde_07_loginc = this->gaintilde_07_loginc;
    auto __gaintilde_07_zval = this->gaintilde_07_zval;
    auto __gaintilde_07_value = this->gaintilde_07_value;
    number mult = (__gaintilde_07_value <= 0 ? 0. : __gaintilde_07_zval * rnbo_exp(__gaintilde_07_value * __gaintilde_07_loginc));
    auto iv = this->mstosamps(__gaintilde_07_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_07_ramp_next(mult, iv, iv);
    }
}

void gaintilde_08_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_08_interp = this->gaintilde_08_interp;
    auto __gaintilde_08_loginc = this->gaintilde_08_loginc;
    auto __gaintilde_08_zval = this->gaintilde_08_zval;
    auto __gaintilde_08_value = this->gaintilde_08_value;
    number mult = (__gaintilde_08_value <= 0 ? 0. : __gaintilde_08_zval * rnbo_exp(__gaintilde_08_value * __gaintilde_08_loginc));
    auto iv = this->mstosamps(__gaintilde_08_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_08_ramp_next(mult, iv, iv);
    }
}

void gaintilde_09_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_09_interp = this->gaintilde_09_interp;
    auto __gaintilde_09_loginc = this->gaintilde_09_loginc;
    auto __gaintilde_09_zval = this->gaintilde_09_zval;
    auto __gaintilde_09_value = this->gaintilde_09_value;
    number mult = (__gaintilde_09_value <= 0 ? 0. : __gaintilde_09_zval * rnbo_exp(__gaintilde_09_value * __gaintilde_09_loginc));
    auto iv = this->mstosamps(__gaintilde_09_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_09_ramp_next(mult, iv, iv);
    }
}

void gaintilde_10_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_10_interp = this->gaintilde_10_interp;
    auto __gaintilde_10_loginc = this->gaintilde_10_loginc;
    auto __gaintilde_10_zval = this->gaintilde_10_zval;
    auto __gaintilde_10_value = this->gaintilde_10_value;
    number mult = (__gaintilde_10_value <= 0 ? 0. : __gaintilde_10_zval * rnbo_exp(__gaintilde_10_value * __gaintilde_10_loginc));
    auto iv = this->mstosamps(__gaintilde_10_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_10_ramp_next(mult, iv, iv);
    }
}

void gaintilde_11_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_11_interp = this->gaintilde_11_interp;
    auto __gaintilde_11_loginc = this->gaintilde_11_loginc;
    auto __gaintilde_11_zval = this->gaintilde_11_zval;
    auto __gaintilde_11_value = this->gaintilde_11_value;
    number mult = (__gaintilde_11_value <= 0 ? 0. : __gaintilde_11_zval * rnbo_exp(__gaintilde_11_value * __gaintilde_11_loginc));
    auto iv = this->mstosamps(__gaintilde_11_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_11_ramp_next(mult, iv, iv);
    }
}

void gaintilde_12_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_12_interp = this->gaintilde_12_interp;
    auto __gaintilde_12_loginc = this->gaintilde_12_loginc;
    auto __gaintilde_12_zval = this->gaintilde_12_zval;
    auto __gaintilde_12_value = this->gaintilde_12_value;
    number mult = (__gaintilde_12_value <= 0 ? 0. : __gaintilde_12_zval * rnbo_exp(__gaintilde_12_value * __gaintilde_12_loginc));
    auto iv = this->mstosamps(__gaintilde_12_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_12_ramp_next(mult, iv, iv);
    }
}

void gaintilde_13_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_13_interp = this->gaintilde_13_interp;
    auto __gaintilde_13_loginc = this->gaintilde_13_loginc;
    auto __gaintilde_13_zval = this->gaintilde_13_zval;
    auto __gaintilde_13_value = this->gaintilde_13_value;
    number mult = (__gaintilde_13_value <= 0 ? 0. : __gaintilde_13_zval * rnbo_exp(__gaintilde_13_value * __gaintilde_13_loginc));
    auto iv = this->mstosamps(__gaintilde_13_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_13_ramp_next(mult, iv, iv);
    }
}

void gaintilde_14_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_14_interp = this->gaintilde_14_interp;
    auto __gaintilde_14_loginc = this->gaintilde_14_loginc;
    auto __gaintilde_14_zval = this->gaintilde_14_zval;
    auto __gaintilde_14_value = this->gaintilde_14_value;
    number mult = (__gaintilde_14_value <= 0 ? 0. : __gaintilde_14_zval * rnbo_exp(__gaintilde_14_value * __gaintilde_14_loginc));
    auto iv = this->mstosamps(__gaintilde_14_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_14_ramp_next(mult, iv, iv);
    }
}

void gaintilde_15_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_15_interp = this->gaintilde_15_interp;
    auto __gaintilde_15_loginc = this->gaintilde_15_loginc;
    auto __gaintilde_15_zval = this->gaintilde_15_zval;
    auto __gaintilde_15_value = this->gaintilde_15_value;
    number mult = (__gaintilde_15_value <= 0 ? 0. : __gaintilde_15_zval * rnbo_exp(__gaintilde_15_value * __gaintilde_15_loginc));
    auto iv = this->mstosamps(__gaintilde_15_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_15_ramp_next(mult, iv, iv);
    }
}

void gaintilde_16_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __gaintilde_16_interp = this->gaintilde_16_interp;
    auto __gaintilde_16_loginc = this->gaintilde_16_loginc;
    auto __gaintilde_16_zval = this->gaintilde_16_zval;
    auto __gaintilde_16_value = this->gaintilde_16_value;
    number mult = (__gaintilde_16_value <= 0 ? 0. : __gaintilde_16_zval * rnbo_exp(__gaintilde_16_value * __gaintilde_16_loginc));
    auto iv = this->mstosamps(__gaintilde_16_interp);

    for (Index i = 0; i < n; i++) {
        output[(Index)i] = input_signal[(Index)i] * this->gaintilde_16_ramp_next(mult, iv, iv);
    }
}

void dspexpr_01_perform(number in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    RNBO_UNUSED(in1);
    Index i;

    for (i = 0; i < n; i++) {
        out1[(Index)i] = 0 * 0.001;//#map:_###_obj_###_:1
    }
}

void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
    auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
    auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
    auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
    auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
    auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
    number monitorvalue = input_signal[0];

    for (Index i = 0; i < n; i++) {
        if (__numbertilde_01_currentMode == 0) {
            output[(Index)i] = this->numbertilde_01_smooth_next(
                __numbertilde_01_outValue,
                __numbertilde_01_rampInSamples,
                __numbertilde_01_rampInSamples
            );
        } else {
            output[(Index)i] = input_signal[(Index)i];
        }
    }

    __numbertilde_01_currentInterval -= n;

    if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
        __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;

        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1494586265,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            monitorvalue
        );;

        __numbertilde_01_lastValue = monitorvalue;
        this->getEngine()->sendListMessage(TAG("monitor"), TAG("number~_obj-147"), {monitorvalue}, this->_currentTime);;
    }

    this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
    this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_01_srout_set(number v) {
    this->numberobj_04_value_set(v);
}

void data_01_chanout_set(number v) {
    this->numberobj_03_value_set(v);
}

void data_01_sizeout_set(number v) {
    this->data_01_sizeout = v;
    this->numberobj_02_value_set(v);
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void toggle_01_value_number_setter(number v) {
    this->toggle_01_value_number = (v != 0 ? 1 : 0);
}

void numberobj_02_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_02_value = localvalue;
}

void numberobj_03_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_03_value = localvalue;
}

void numberobj_04_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_04_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_04_value = localvalue;
}

void numberobj_05_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_05_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_05_value = localvalue;
}

void numberobj_06_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_06_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_06_value = localvalue;
}

void numberobj_07_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_07_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_07_value = localvalue;
}

void numberobj_08_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_08_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_08_value = localvalue;
}

void numberobj_09_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_09_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_09_value = localvalue;
}

void numberobj_10_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_10_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_10_value = localvalue;
}

void numberobj_11_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_11_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_11_value = localvalue;
}

void numberobj_12_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_12_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_12_value = localvalue;
}

void numberobj_13_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_13_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_13_value = localvalue;
}

void numberobj_14_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_14_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_14_value = localvalue;
}

void numberobj_15_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_15_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_15_value = localvalue;
}

void numberobj_16_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_16_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_16_value = localvalue;
}

void numberobj_17_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_17_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_17_value = localvalue;
}

void numberobj_18_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_18_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_18_value = localvalue;
}

void numberobj_19_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_19_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_19_value = localvalue;
}

void numberobj_20_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_20_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_20_value = localvalue;
}

void numberobj_21_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_21_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_21_value = localvalue;
}

void numberobj_22_value_setter(number v) {
    number localvalue = v;

    if ((bool)(true) && localvalue < 0) {
        localvalue = 0;
    }

    if ((bool)(true) && localvalue > 150) {
        localvalue = 150;
    }

    if (this->numberobj_22_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_22_value = localvalue;
}

void numberobj_23_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_23_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_23_value = localvalue;
}

number gaintilde_01_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_01_ramp_d_prev);
    this->gaintilde_01_ramp_d_prev = x;
    return temp;
}

void gaintilde_01_ramp_d_dspsetup() {
    this->gaintilde_01_ramp_d_reset();
}

void gaintilde_01_ramp_d_reset() {
    this->gaintilde_01_ramp_d_prev = 0;
}

number gaintilde_01_ramp_next(number x, number up, number down) {
    if (this->gaintilde_01_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_01_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_01_ramp_index = _up;
            this->gaintilde_01_ramp_increment = (x - this->gaintilde_01_ramp_prev) / _up;
        } else if (x < this->gaintilde_01_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_01_ramp_index = _down;
            this->gaintilde_01_ramp_increment = (x - this->gaintilde_01_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_01_ramp_index > 0) {
        this->gaintilde_01_ramp_prev += this->gaintilde_01_ramp_increment;
        this->gaintilde_01_ramp_index -= 1;
    } else {
        this->gaintilde_01_ramp_prev = x;
    }

    return this->gaintilde_01_ramp_prev;
}

void gaintilde_01_ramp_reset() {
    this->gaintilde_01_ramp_prev = 0;
    this->gaintilde_01_ramp_index = 0;
    this->gaintilde_01_ramp_increment = 0;
    this->gaintilde_01_ramp_d_reset();
}

void gaintilde_01_init() {
    this->gaintilde_01_loginc = rnbo_log(1.072);
    this->gaintilde_01_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_01_loginc));
}

void gaintilde_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_01_value;
}

void gaintilde_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_01_value_set(preset["value"]);
}

void gaintilde_01_dspsetup(bool force) {
    if ((bool)(this->gaintilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_01_setupDone = true;
    this->gaintilde_01_ramp_d_dspsetup();
}

number groove_01_getSample(
    Index channel,
    SampleIndex index,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    if (offset > 0) {
        index += offset;

        if (index >= bufferLength)
            index -= bufferLength;
    }

    return this->groove_01_buffer->getSample(channel, index);
}

number groove_01_interpolatedSample(
    Index channel,
    number index,
    SampleIndex end,
    SampleIndex length,
    SampleIndex offset,
    SampleIndex bufferLength
) {
    SampleIndex index1 = (SampleIndex)(trunc(index));
    number i_x = index - index1;
    number i_1px = 1. + i_x;
    number i_1mx = 1. - i_x;
    number i_2mx = 2. - i_x;
    number i_a = i_1mx * i_2mx;
    number i_b = i_1px * i_x;
    number i_p1 = -.1666667 * i_a * i_x;
    number i_p2 = .5 * i_1px * i_a;
    number i_p3 = .5 * i_b * i_2mx;
    number i_p4 = -.1666667 * i_b * i_1mx;
    SampleIndex index2 = (SampleIndex)(index1 + 1);

    if (index2 >= end)
        index2 -= length;

    SampleIndex index3 = (SampleIndex)(index1 + 2);

    if (index3 >= end)
        index3 -= length;

    SampleIndex index4 = (SampleIndex)(index1 + 3);

    if (index4 >= end)
        index4 -= length;

    return this->groove_01_getSample(channel, index1, offset, bufferLength) * i_p1 + this->groove_01_getSample(channel, index2, offset, bufferLength) * i_p2 + this->groove_01_getSample(channel, index3, offset, bufferLength) * i_p3 + this->groove_01_getSample(channel, index4, offset, bufferLength) * i_p4;
}

number groove_01_crossfadedSample(
    SampleValue out,
    number readIndex,
    Index channel,
    number rate,
    number loopMin,
    number loopMax,
    number loopLength,
    number offset,
    number bufferLength
) {
    auto crossFadeStart1 = this->maximum(loopMin - this->groove_01_crossfadeInSamples, 0);
    auto crossFadeEnd1 = this->minimum(crossFadeStart1 + this->groove_01_crossfadeInSamples, bufferLength);
    number crossFadeStart2 = crossFadeStart1 + loopLength;
    auto crossFadeEnd2 = this->minimum(crossFadeEnd1 + loopLength, bufferLength);
    number crossFadeLength = crossFadeEnd2 - crossFadeStart2;

    if (crossFadeLength > 0) {
        crossFadeEnd1 = crossFadeStart1 + crossFadeLength;
        number diff = -1;
        number addFactor = 0;

        if (readIndex >= crossFadeStart2) {
            diff = readIndex - crossFadeStart2;
            addFactor = -1;
        } else if (readIndex < crossFadeEnd1) {
            diff = crossFadeEnd1 - readIndex + loopMax - crossFadeStart2;
            addFactor = 1;
        }

        if (diff >= 0) {
            number out2ReadIndex = readIndex + loopLength * addFactor;
            number out2 = (rate == 1 ? this->groove_01_getSample(channel, trunc(out2ReadIndex), offset, bufferLength) : this->groove_01_interpolatedSample(channel, out2ReadIndex, loopMax, loopLength, offset, bufferLength));
            number out2Factor = diff / crossFadeLength;
            number out1Factor = 1 - out2Factor;
            return out * out1Factor + out2 * out2Factor;
        }
    }

    return out;
}

number groove_01_calcSync(
    number readIndex,
    number offset,
    number loopMin,
    number loopLength,
    SampleIndex bufferLength,
    number srInv
) {
    RNBO_UNUSED(loopLength);
    RNBO_UNUSED(loopMin);

    {
        if (offset > 0) {
            readIndex += offset;

            if (readIndex >= bufferLength)
                readIndex -= bufferLength;
        }

        {
            {
                {
                    return readIndex * srInv * 1000;
                }
            }
        }
    }
}

void groove_01_dspsetup(bool force) {
    if ((bool)(this->groove_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->groove_01_crossfadeInSamples = this->mstosamps(this->groove_01_crossfade);
    this->groove_01_setupDone = true;
}

number gaintilde_02_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_02_ramp_d_prev);
    this->gaintilde_02_ramp_d_prev = x;
    return temp;
}

void gaintilde_02_ramp_d_dspsetup() {
    this->gaintilde_02_ramp_d_reset();
}

void gaintilde_02_ramp_d_reset() {
    this->gaintilde_02_ramp_d_prev = 0;
}

number gaintilde_02_ramp_next(number x, number up, number down) {
    if (this->gaintilde_02_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_02_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_02_ramp_index = _up;
            this->gaintilde_02_ramp_increment = (x - this->gaintilde_02_ramp_prev) / _up;
        } else if (x < this->gaintilde_02_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_02_ramp_index = _down;
            this->gaintilde_02_ramp_increment = (x - this->gaintilde_02_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_02_ramp_index > 0) {
        this->gaintilde_02_ramp_prev += this->gaintilde_02_ramp_increment;
        this->gaintilde_02_ramp_index -= 1;
    } else {
        this->gaintilde_02_ramp_prev = x;
    }

    return this->gaintilde_02_ramp_prev;
}

void gaintilde_02_ramp_reset() {
    this->gaintilde_02_ramp_prev = 0;
    this->gaintilde_02_ramp_index = 0;
    this->gaintilde_02_ramp_increment = 0;
    this->gaintilde_02_ramp_d_reset();
}

void gaintilde_02_init() {
    this->gaintilde_02_loginc = rnbo_log(1.072);
    this->gaintilde_02_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_02_loginc));
}

void gaintilde_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_02_value;
}

void gaintilde_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_02_value_set(preset["value"]);
}

void gaintilde_02_dspsetup(bool force) {
    if ((bool)(this->gaintilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_02_setupDone = true;
    this->gaintilde_02_ramp_d_dspsetup();
}

number gaintilde_03_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_03_ramp_d_prev);
    this->gaintilde_03_ramp_d_prev = x;
    return temp;
}

void gaintilde_03_ramp_d_dspsetup() {
    this->gaintilde_03_ramp_d_reset();
}

void gaintilde_03_ramp_d_reset() {
    this->gaintilde_03_ramp_d_prev = 0;
}

number gaintilde_03_ramp_next(number x, number up, number down) {
    if (this->gaintilde_03_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_03_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_03_ramp_index = _up;
            this->gaintilde_03_ramp_increment = (x - this->gaintilde_03_ramp_prev) / _up;
        } else if (x < this->gaintilde_03_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_03_ramp_index = _down;
            this->gaintilde_03_ramp_increment = (x - this->gaintilde_03_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_03_ramp_index > 0) {
        this->gaintilde_03_ramp_prev += this->gaintilde_03_ramp_increment;
        this->gaintilde_03_ramp_index -= 1;
    } else {
        this->gaintilde_03_ramp_prev = x;
    }

    return this->gaintilde_03_ramp_prev;
}

void gaintilde_03_ramp_reset() {
    this->gaintilde_03_ramp_prev = 0;
    this->gaintilde_03_ramp_index = 0;
    this->gaintilde_03_ramp_increment = 0;
    this->gaintilde_03_ramp_d_reset();
}

void gaintilde_03_init() {
    this->gaintilde_03_loginc = rnbo_log(1.072);
    this->gaintilde_03_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_03_loginc));
}

void gaintilde_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_03_value;
}

void gaintilde_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_03_value_set(preset["value"]);
}

void gaintilde_03_dspsetup(bool force) {
    if ((bool)(this->gaintilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_03_setupDone = true;
    this->gaintilde_03_ramp_d_dspsetup();
}

number gaintilde_04_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_04_ramp_d_prev);
    this->gaintilde_04_ramp_d_prev = x;
    return temp;
}

void gaintilde_04_ramp_d_dspsetup() {
    this->gaintilde_04_ramp_d_reset();
}

void gaintilde_04_ramp_d_reset() {
    this->gaintilde_04_ramp_d_prev = 0;
}

number gaintilde_04_ramp_next(number x, number up, number down) {
    if (this->gaintilde_04_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_04_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_04_ramp_index = _up;
            this->gaintilde_04_ramp_increment = (x - this->gaintilde_04_ramp_prev) / _up;
        } else if (x < this->gaintilde_04_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_04_ramp_index = _down;
            this->gaintilde_04_ramp_increment = (x - this->gaintilde_04_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_04_ramp_index > 0) {
        this->gaintilde_04_ramp_prev += this->gaintilde_04_ramp_increment;
        this->gaintilde_04_ramp_index -= 1;
    } else {
        this->gaintilde_04_ramp_prev = x;
    }

    return this->gaintilde_04_ramp_prev;
}

void gaintilde_04_ramp_reset() {
    this->gaintilde_04_ramp_prev = 0;
    this->gaintilde_04_ramp_index = 0;
    this->gaintilde_04_ramp_increment = 0;
    this->gaintilde_04_ramp_d_reset();
}

void gaintilde_04_init() {
    this->gaintilde_04_loginc = rnbo_log(1.072);
    this->gaintilde_04_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_04_loginc));
}

void gaintilde_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_04_value;
}

void gaintilde_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_04_value_set(preset["value"]);
}

void gaintilde_04_dspsetup(bool force) {
    if ((bool)(this->gaintilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_04_setupDone = true;
    this->gaintilde_04_ramp_d_dspsetup();
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-3"), 1, this->_currentTime);
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
}

void message_01_init() {
    this->message_01_set_set({8});
}

number gaintilde_05_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_05_ramp_d_prev);
    this->gaintilde_05_ramp_d_prev = x;
    return temp;
}

void gaintilde_05_ramp_d_dspsetup() {
    this->gaintilde_05_ramp_d_reset();
}

void gaintilde_05_ramp_d_reset() {
    this->gaintilde_05_ramp_d_prev = 0;
}

number gaintilde_05_ramp_next(number x, number up, number down) {
    if (this->gaintilde_05_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_05_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_05_ramp_index = _up;
            this->gaintilde_05_ramp_increment = (x - this->gaintilde_05_ramp_prev) / _up;
        } else if (x < this->gaintilde_05_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_05_ramp_index = _down;
            this->gaintilde_05_ramp_increment = (x - this->gaintilde_05_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_05_ramp_index > 0) {
        this->gaintilde_05_ramp_prev += this->gaintilde_05_ramp_increment;
        this->gaintilde_05_ramp_index -= 1;
    } else {
        this->gaintilde_05_ramp_prev = x;
    }

    return this->gaintilde_05_ramp_prev;
}

void gaintilde_05_ramp_reset() {
    this->gaintilde_05_ramp_prev = 0;
    this->gaintilde_05_ramp_index = 0;
    this->gaintilde_05_ramp_increment = 0;
    this->gaintilde_05_ramp_d_reset();
}

void gaintilde_05_init() {
    this->gaintilde_05_loginc = rnbo_log(1.072);
    this->gaintilde_05_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_05_loginc));
}

void gaintilde_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_05_value;
}

void gaintilde_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_05_value_set(preset["value"]);
}

void gaintilde_05_dspsetup(bool force) {
    if ((bool)(this->gaintilde_05_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_05_setupDone = true;
    this->gaintilde_05_ramp_d_dspsetup();
}

number gaintilde_06_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_06_ramp_d_prev);
    this->gaintilde_06_ramp_d_prev = x;
    return temp;
}

void gaintilde_06_ramp_d_dspsetup() {
    this->gaintilde_06_ramp_d_reset();
}

void gaintilde_06_ramp_d_reset() {
    this->gaintilde_06_ramp_d_prev = 0;
}

number gaintilde_06_ramp_next(number x, number up, number down) {
    if (this->gaintilde_06_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_06_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_06_ramp_index = _up;
            this->gaintilde_06_ramp_increment = (x - this->gaintilde_06_ramp_prev) / _up;
        } else if (x < this->gaintilde_06_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_06_ramp_index = _down;
            this->gaintilde_06_ramp_increment = (x - this->gaintilde_06_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_06_ramp_index > 0) {
        this->gaintilde_06_ramp_prev += this->gaintilde_06_ramp_increment;
        this->gaintilde_06_ramp_index -= 1;
    } else {
        this->gaintilde_06_ramp_prev = x;
    }

    return this->gaintilde_06_ramp_prev;
}

void gaintilde_06_ramp_reset() {
    this->gaintilde_06_ramp_prev = 0;
    this->gaintilde_06_ramp_index = 0;
    this->gaintilde_06_ramp_increment = 0;
    this->gaintilde_06_ramp_d_reset();
}

void gaintilde_06_init() {
    this->gaintilde_06_loginc = rnbo_log(1.072);
    this->gaintilde_06_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_06_loginc));
}

void gaintilde_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_06_value;
}

void gaintilde_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_06_value_set(preset["value"]);
}

void gaintilde_06_dspsetup(bool force) {
    if ((bool)(this->gaintilde_06_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_06_setupDone = true;
    this->gaintilde_06_ramp_d_dspsetup();
}

number gaintilde_07_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_07_ramp_d_prev);
    this->gaintilde_07_ramp_d_prev = x;
    return temp;
}

void gaintilde_07_ramp_d_dspsetup() {
    this->gaintilde_07_ramp_d_reset();
}

void gaintilde_07_ramp_d_reset() {
    this->gaintilde_07_ramp_d_prev = 0;
}

number gaintilde_07_ramp_next(number x, number up, number down) {
    if (this->gaintilde_07_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_07_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_07_ramp_index = _up;
            this->gaintilde_07_ramp_increment = (x - this->gaintilde_07_ramp_prev) / _up;
        } else if (x < this->gaintilde_07_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_07_ramp_index = _down;
            this->gaintilde_07_ramp_increment = (x - this->gaintilde_07_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_07_ramp_index > 0) {
        this->gaintilde_07_ramp_prev += this->gaintilde_07_ramp_increment;
        this->gaintilde_07_ramp_index -= 1;
    } else {
        this->gaintilde_07_ramp_prev = x;
    }

    return this->gaintilde_07_ramp_prev;
}

void gaintilde_07_ramp_reset() {
    this->gaintilde_07_ramp_prev = 0;
    this->gaintilde_07_ramp_index = 0;
    this->gaintilde_07_ramp_increment = 0;
    this->gaintilde_07_ramp_d_reset();
}

void gaintilde_07_init() {
    this->gaintilde_07_loginc = rnbo_log(1.072);
    this->gaintilde_07_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_07_loginc));
}

void gaintilde_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_07_value;
}

void gaintilde_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_07_value_set(preset["value"]);
}

void gaintilde_07_dspsetup(bool force) {
    if ((bool)(this->gaintilde_07_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_07_setupDone = true;
    this->gaintilde_07_ramp_d_dspsetup();
}

number gaintilde_08_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_08_ramp_d_prev);
    this->gaintilde_08_ramp_d_prev = x;
    return temp;
}

void gaintilde_08_ramp_d_dspsetup() {
    this->gaintilde_08_ramp_d_reset();
}

void gaintilde_08_ramp_d_reset() {
    this->gaintilde_08_ramp_d_prev = 0;
}

number gaintilde_08_ramp_next(number x, number up, number down) {
    if (this->gaintilde_08_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_08_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_08_ramp_index = _up;
            this->gaintilde_08_ramp_increment = (x - this->gaintilde_08_ramp_prev) / _up;
        } else if (x < this->gaintilde_08_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_08_ramp_index = _down;
            this->gaintilde_08_ramp_increment = (x - this->gaintilde_08_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_08_ramp_index > 0) {
        this->gaintilde_08_ramp_prev += this->gaintilde_08_ramp_increment;
        this->gaintilde_08_ramp_index -= 1;
    } else {
        this->gaintilde_08_ramp_prev = x;
    }

    return this->gaintilde_08_ramp_prev;
}

void gaintilde_08_ramp_reset() {
    this->gaintilde_08_ramp_prev = 0;
    this->gaintilde_08_ramp_index = 0;
    this->gaintilde_08_ramp_increment = 0;
    this->gaintilde_08_ramp_d_reset();
}

void gaintilde_08_init() {
    this->gaintilde_08_loginc = rnbo_log(1.072);
    this->gaintilde_08_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_08_loginc));
}

void gaintilde_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_08_value;
}

void gaintilde_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_08_value_set(preset["value"]);
}

void gaintilde_08_dspsetup(bool force) {
    if ((bool)(this->gaintilde_08_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_08_setupDone = true;
    this->gaintilde_08_ramp_d_dspsetup();
}

void toggle_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->toggle_01_value_number;
}

void toggle_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->toggle_01_value_number_set(preset["value"]);
}

number gaintilde_09_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_09_ramp_d_prev);
    this->gaintilde_09_ramp_d_prev = x;
    return temp;
}

void gaintilde_09_ramp_d_dspsetup() {
    this->gaintilde_09_ramp_d_reset();
}

void gaintilde_09_ramp_d_reset() {
    this->gaintilde_09_ramp_d_prev = 0;
}

number gaintilde_09_ramp_next(number x, number up, number down) {
    if (this->gaintilde_09_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_09_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_09_ramp_index = _up;
            this->gaintilde_09_ramp_increment = (x - this->gaintilde_09_ramp_prev) / _up;
        } else if (x < this->gaintilde_09_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_09_ramp_index = _down;
            this->gaintilde_09_ramp_increment = (x - this->gaintilde_09_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_09_ramp_index > 0) {
        this->gaintilde_09_ramp_prev += this->gaintilde_09_ramp_increment;
        this->gaintilde_09_ramp_index -= 1;
    } else {
        this->gaintilde_09_ramp_prev = x;
    }

    return this->gaintilde_09_ramp_prev;
}

void gaintilde_09_ramp_reset() {
    this->gaintilde_09_ramp_prev = 0;
    this->gaintilde_09_ramp_index = 0;
    this->gaintilde_09_ramp_increment = 0;
    this->gaintilde_09_ramp_d_reset();
}

void gaintilde_09_init() {
    this->gaintilde_09_loginc = rnbo_log(1.072);
    this->gaintilde_09_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_09_loginc));
}

void gaintilde_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_09_value;
}

void gaintilde_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_09_value_set(preset["value"]);
}

void gaintilde_09_dspsetup(bool force) {
    if ((bool)(this->gaintilde_09_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_09_setupDone = true;
    this->gaintilde_09_ramp_d_dspsetup();
}

void numberobj_02_init() {
    this->numberobj_02_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-6"), 1, this->_currentTime);
}

void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_02_value;
}

void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_02_value_set(preset["value"]);
}

void data_01_init() {
    this->data_01_buffer->setWantsFill(true);
}

Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_01_dspsetup(bool force) {
    if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_01_sizemode == 2) {
        this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
        updateDataRef(this, this->data_01_buffer);
    } else if (this->data_01_sizemode == 3) {
        this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_01_buffer);
    }

    this->data_01_setupDone = true;
}

void data_01_bufferUpdated() {
    this->data_01_report();
}

void data_01_report() {
    this->data_01_srout_set(this->data_01_buffer->getSampleRate());
    this->data_01_chanout_set(this->data_01_buffer->getChannels());
    this->data_01_sizeout_set(this->data_01_buffer->getSize());
}

number gaintilde_10_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_10_ramp_d_prev);
    this->gaintilde_10_ramp_d_prev = x;
    return temp;
}

void gaintilde_10_ramp_d_dspsetup() {
    this->gaintilde_10_ramp_d_reset();
}

void gaintilde_10_ramp_d_reset() {
    this->gaintilde_10_ramp_d_prev = 0;
}

number gaintilde_10_ramp_next(number x, number up, number down) {
    if (this->gaintilde_10_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_10_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_10_ramp_index = _up;
            this->gaintilde_10_ramp_increment = (x - this->gaintilde_10_ramp_prev) / _up;
        } else if (x < this->gaintilde_10_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_10_ramp_index = _down;
            this->gaintilde_10_ramp_increment = (x - this->gaintilde_10_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_10_ramp_index > 0) {
        this->gaintilde_10_ramp_prev += this->gaintilde_10_ramp_increment;
        this->gaintilde_10_ramp_index -= 1;
    } else {
        this->gaintilde_10_ramp_prev = x;
    }

    return this->gaintilde_10_ramp_prev;
}

void gaintilde_10_ramp_reset() {
    this->gaintilde_10_ramp_prev = 0;
    this->gaintilde_10_ramp_index = 0;
    this->gaintilde_10_ramp_increment = 0;
    this->gaintilde_10_ramp_d_reset();
}

void gaintilde_10_init() {
    this->gaintilde_10_loginc = rnbo_log(1.072);
    this->gaintilde_10_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_10_loginc));
}

void gaintilde_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_10_value;
}

void gaintilde_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_10_value_set(preset["value"]);
}

void gaintilde_10_dspsetup(bool force) {
    if ((bool)(this->gaintilde_10_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_10_setupDone = true;
    this->gaintilde_10_ramp_d_dspsetup();
}

number gaintilde_11_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_11_ramp_d_prev);
    this->gaintilde_11_ramp_d_prev = x;
    return temp;
}

void gaintilde_11_ramp_d_dspsetup() {
    this->gaintilde_11_ramp_d_reset();
}

void gaintilde_11_ramp_d_reset() {
    this->gaintilde_11_ramp_d_prev = 0;
}

number gaintilde_11_ramp_next(number x, number up, number down) {
    if (this->gaintilde_11_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_11_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_11_ramp_index = _up;
            this->gaintilde_11_ramp_increment = (x - this->gaintilde_11_ramp_prev) / _up;
        } else if (x < this->gaintilde_11_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_11_ramp_index = _down;
            this->gaintilde_11_ramp_increment = (x - this->gaintilde_11_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_11_ramp_index > 0) {
        this->gaintilde_11_ramp_prev += this->gaintilde_11_ramp_increment;
        this->gaintilde_11_ramp_index -= 1;
    } else {
        this->gaintilde_11_ramp_prev = x;
    }

    return this->gaintilde_11_ramp_prev;
}

void gaintilde_11_ramp_reset() {
    this->gaintilde_11_ramp_prev = 0;
    this->gaintilde_11_ramp_index = 0;
    this->gaintilde_11_ramp_increment = 0;
    this->gaintilde_11_ramp_d_reset();
}

void gaintilde_11_init() {
    this->gaintilde_11_loginc = rnbo_log(1.072);
    this->gaintilde_11_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_11_loginc));
}

void gaintilde_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_11_value;
}

void gaintilde_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_11_value_set(preset["value"]);
}

void gaintilde_11_dspsetup(bool force) {
    if ((bool)(this->gaintilde_11_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_11_setupDone = true;
    this->gaintilde_11_ramp_d_dspsetup();
}

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-4"), 1, this->_currentTime);
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

number gaintilde_12_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_12_ramp_d_prev);
    this->gaintilde_12_ramp_d_prev = x;
    return temp;
}

void gaintilde_12_ramp_d_dspsetup() {
    this->gaintilde_12_ramp_d_reset();
}

void gaintilde_12_ramp_d_reset() {
    this->gaintilde_12_ramp_d_prev = 0;
}

number gaintilde_12_ramp_next(number x, number up, number down) {
    if (this->gaintilde_12_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_12_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_12_ramp_index = _up;
            this->gaintilde_12_ramp_increment = (x - this->gaintilde_12_ramp_prev) / _up;
        } else if (x < this->gaintilde_12_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_12_ramp_index = _down;
            this->gaintilde_12_ramp_increment = (x - this->gaintilde_12_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_12_ramp_index > 0) {
        this->gaintilde_12_ramp_prev += this->gaintilde_12_ramp_increment;
        this->gaintilde_12_ramp_index -= 1;
    } else {
        this->gaintilde_12_ramp_prev = x;
    }

    return this->gaintilde_12_ramp_prev;
}

void gaintilde_12_ramp_reset() {
    this->gaintilde_12_ramp_prev = 0;
    this->gaintilde_12_ramp_index = 0;
    this->gaintilde_12_ramp_increment = 0;
    this->gaintilde_12_ramp_d_reset();
}

void gaintilde_12_init() {
    this->gaintilde_12_loginc = rnbo_log(1.072);
    this->gaintilde_12_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_12_loginc));
}

void gaintilde_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_12_value;
}

void gaintilde_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_12_value_set(preset["value"]);
}

void gaintilde_12_dspsetup(bool force) {
    if ((bool)(this->gaintilde_12_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_12_setupDone = true;
    this->gaintilde_12_ramp_d_dspsetup();
}

number gaintilde_13_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_13_ramp_d_prev);
    this->gaintilde_13_ramp_d_prev = x;
    return temp;
}

void gaintilde_13_ramp_d_dspsetup() {
    this->gaintilde_13_ramp_d_reset();
}

void gaintilde_13_ramp_d_reset() {
    this->gaintilde_13_ramp_d_prev = 0;
}

number gaintilde_13_ramp_next(number x, number up, number down) {
    if (this->gaintilde_13_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_13_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_13_ramp_index = _up;
            this->gaintilde_13_ramp_increment = (x - this->gaintilde_13_ramp_prev) / _up;
        } else if (x < this->gaintilde_13_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_13_ramp_index = _down;
            this->gaintilde_13_ramp_increment = (x - this->gaintilde_13_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_13_ramp_index > 0) {
        this->gaintilde_13_ramp_prev += this->gaintilde_13_ramp_increment;
        this->gaintilde_13_ramp_index -= 1;
    } else {
        this->gaintilde_13_ramp_prev = x;
    }

    return this->gaintilde_13_ramp_prev;
}

void gaintilde_13_ramp_reset() {
    this->gaintilde_13_ramp_prev = 0;
    this->gaintilde_13_ramp_index = 0;
    this->gaintilde_13_ramp_increment = 0;
    this->gaintilde_13_ramp_d_reset();
}

void gaintilde_13_init() {
    this->gaintilde_13_loginc = rnbo_log(1.072);
    this->gaintilde_13_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_13_loginc));
}

void gaintilde_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_13_value;
}

void gaintilde_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_13_value_set(preset["value"]);
}

void gaintilde_13_dspsetup(bool force) {
    if ((bool)(this->gaintilde_13_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_13_setupDone = true;
    this->gaintilde_13_ramp_d_dspsetup();
}

void numberobj_04_init() {
    this->numberobj_04_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-113"), 1, this->_currentTime);
}

void numberobj_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_04_value;
}

void numberobj_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_04_value_set(preset["value"]);
}

number gaintilde_14_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_14_ramp_d_prev);
    this->gaintilde_14_ramp_d_prev = x;
    return temp;
}

void gaintilde_14_ramp_d_dspsetup() {
    this->gaintilde_14_ramp_d_reset();
}

void gaintilde_14_ramp_d_reset() {
    this->gaintilde_14_ramp_d_prev = 0;
}

number gaintilde_14_ramp_next(number x, number up, number down) {
    if (this->gaintilde_14_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_14_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_14_ramp_index = _up;
            this->gaintilde_14_ramp_increment = (x - this->gaintilde_14_ramp_prev) / _up;
        } else if (x < this->gaintilde_14_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_14_ramp_index = _down;
            this->gaintilde_14_ramp_increment = (x - this->gaintilde_14_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_14_ramp_index > 0) {
        this->gaintilde_14_ramp_prev += this->gaintilde_14_ramp_increment;
        this->gaintilde_14_ramp_index -= 1;
    } else {
        this->gaintilde_14_ramp_prev = x;
    }

    return this->gaintilde_14_ramp_prev;
}

void gaintilde_14_ramp_reset() {
    this->gaintilde_14_ramp_prev = 0;
    this->gaintilde_14_ramp_index = 0;
    this->gaintilde_14_ramp_increment = 0;
    this->gaintilde_14_ramp_d_reset();
}

void gaintilde_14_init() {
    this->gaintilde_14_loginc = rnbo_log(1.072);
    this->gaintilde_14_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_14_loginc));
}

void gaintilde_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_14_value;
}

void gaintilde_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_14_value_set(preset["value"]);
}

void gaintilde_14_dspsetup(bool force) {
    if ((bool)(this->gaintilde_14_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_14_setupDone = true;
    this->gaintilde_14_ramp_d_dspsetup();
}

void numberobj_05_init() {
    this->numberobj_05_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-103"), 1, this->_currentTime);
}

void numberobj_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_05_value;
}

void numberobj_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_05_value_set(preset["value"]);
}

number gaintilde_15_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_15_ramp_d_prev);
    this->gaintilde_15_ramp_d_prev = x;
    return temp;
}

void gaintilde_15_ramp_d_dspsetup() {
    this->gaintilde_15_ramp_d_reset();
}

void gaintilde_15_ramp_d_reset() {
    this->gaintilde_15_ramp_d_prev = 0;
}

number gaintilde_15_ramp_next(number x, number up, number down) {
    if (this->gaintilde_15_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_15_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_15_ramp_index = _up;
            this->gaintilde_15_ramp_increment = (x - this->gaintilde_15_ramp_prev) / _up;
        } else if (x < this->gaintilde_15_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_15_ramp_index = _down;
            this->gaintilde_15_ramp_increment = (x - this->gaintilde_15_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_15_ramp_index > 0) {
        this->gaintilde_15_ramp_prev += this->gaintilde_15_ramp_increment;
        this->gaintilde_15_ramp_index -= 1;
    } else {
        this->gaintilde_15_ramp_prev = x;
    }

    return this->gaintilde_15_ramp_prev;
}

void gaintilde_15_ramp_reset() {
    this->gaintilde_15_ramp_prev = 0;
    this->gaintilde_15_ramp_index = 0;
    this->gaintilde_15_ramp_increment = 0;
    this->gaintilde_15_ramp_d_reset();
}

void gaintilde_15_init() {
    this->gaintilde_15_loginc = rnbo_log(1.072);
    this->gaintilde_15_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_15_loginc));
}

void gaintilde_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_15_value;
}

void gaintilde_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_15_value_set(preset["value"]);
}

void gaintilde_15_dspsetup(bool force) {
    if ((bool)(this->gaintilde_15_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_15_setupDone = true;
    this->gaintilde_15_ramp_d_dspsetup();
}

number gaintilde_16_ramp_d_next(number x) {
    number temp = (number)(x - this->gaintilde_16_ramp_d_prev);
    this->gaintilde_16_ramp_d_prev = x;
    return temp;
}

void gaintilde_16_ramp_d_dspsetup() {
    this->gaintilde_16_ramp_d_reset();
}

void gaintilde_16_ramp_d_reset() {
    this->gaintilde_16_ramp_d_prev = 0;
}

number gaintilde_16_ramp_next(number x, number up, number down) {
    if (this->gaintilde_16_ramp_d_next(x) != 0.) {
        if (x > this->gaintilde_16_ramp_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->gaintilde_16_ramp_index = _up;
            this->gaintilde_16_ramp_increment = (x - this->gaintilde_16_ramp_prev) / _up;
        } else if (x < this->gaintilde_16_ramp_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->gaintilde_16_ramp_index = _down;
            this->gaintilde_16_ramp_increment = (x - this->gaintilde_16_ramp_prev) / _down;
        }
    }

    if (this->gaintilde_16_ramp_index > 0) {
        this->gaintilde_16_ramp_prev += this->gaintilde_16_ramp_increment;
        this->gaintilde_16_ramp_index -= 1;
    } else {
        this->gaintilde_16_ramp_prev = x;
    }

    return this->gaintilde_16_ramp_prev;
}

void gaintilde_16_ramp_reset() {
    this->gaintilde_16_ramp_prev = 0;
    this->gaintilde_16_ramp_index = 0;
    this->gaintilde_16_ramp_increment = 0;
    this->gaintilde_16_ramp_d_reset();
}

void gaintilde_16_init() {
    this->gaintilde_16_loginc = rnbo_log(1.072);
    this->gaintilde_16_zval = 7.943 * rnbo_exp(-((158 - 1) * this->gaintilde_16_loginc));
}

void gaintilde_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->gaintilde_16_value;
}

void gaintilde_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->gaintilde_16_value_set(preset["value"]);
}

void gaintilde_16_dspsetup(bool force) {
    if ((bool)(this->gaintilde_16_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gaintilde_16_setupDone = true;
    this->gaintilde_16_ramp_d_dspsetup();
}

number numbertilde_01_smooth_d_next(number x) {
    number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
    this->numbertilde_01_smooth_d_prev = x;
    return temp;
}

void numbertilde_01_smooth_d_dspsetup() {
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_smooth_d_reset() {
    this->numbertilde_01_smooth_d_prev = 0;
}

number numbertilde_01_smooth_next(number x, number up, number down) {
    if (this->numbertilde_01_smooth_d_next(x) != 0.) {
        if (x > this->numbertilde_01_smooth_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->numbertilde_01_smooth_index = _up;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
        } else if (x < this->numbertilde_01_smooth_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->numbertilde_01_smooth_index = _down;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
        }
    }

    if (this->numbertilde_01_smooth_index > 0) {
        this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
        this->numbertilde_01_smooth_index -= 1;
    } else {
        this->numbertilde_01_smooth_prev = x;
    }

    return this->numbertilde_01_smooth_prev;
}

void numbertilde_01_smooth_reset() {
    this->numbertilde_01_smooth_prev = 0;
    this->numbertilde_01_smooth_index = 0;
    this->numbertilde_01_smooth_increment = 0;
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_init() {
    this->numbertilde_01_currentMode = 1;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number~_obj-147"), 1, this->_currentTime);
}

void numbertilde_01_dspsetup(bool force) {
    if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
    this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
    this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
    this->numbertilde_01_setupDone = true;
    this->numbertilde_01_smooth_d_dspsetup();
}

void numberobj_06_init() {
    this->numberobj_06_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-152"), 1, this->_currentTime);
}

void numberobj_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_06_value;
}

void numberobj_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_06_value_set(preset["value"]);
}

void numberobj_07_init() {
    this->numberobj_07_currentFormat = 0;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-159"), 1, this->_currentTime);
}

void numberobj_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_07_value;
}

void numberobj_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_07_value_set(preset["value"]);
}

void message_02_init() {
    this->message_02_set_set({1});
}

void data_02_init() {
    this->data_02_buffer->setWantsFill(true);
}

void data_02_report() {
    this->data_02_srout_set(this->data_02_buffer->getSampleRate());
    this->data_02_chanout_set(this->data_02_buffer->getChannels());
    this->data_02_sizeout_set(this->data_02_buffer->getSize());
}

Index data_02_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_02_dspsetup(bool force) {
    if ((bool)(this->data_02_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_02_sizemode == 2) {
        this->data_02_buffer = this->data_02_buffer->setSize((Index)(this->mstosamps(this->data_02_sizems)));
        updateDataRef(this, this->data_02_buffer);
    } else if (this->data_02_sizemode == 3) {
        this->data_02_buffer = this->data_02_buffer->setSize(this->data_02_evaluateSizeExpr(this->samplerate(), this->vectorsize()));
        updateDataRef(this, this->data_02_buffer);
    }

    this->data_02_setupDone = true;
}

void data_02_bufferUpdated() {
    this->data_02_report();
}

void numberobj_08_init() {
    this->numberobj_08_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-60"), 1, this->_currentTime);
}

void numberobj_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_08_value;
}

void numberobj_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_08_value_set(preset["value"]);
}

void numberobj_09_init() {
    this->numberobj_09_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-136"), 1, this->_currentTime);
}

void numberobj_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_09_value;
}

void numberobj_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_09_value_set(preset["value"]);
}

void numberobj_10_init() {
    this->numberobj_10_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-143"), 1, this->_currentTime);
}

void numberobj_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_10_value;
}

void numberobj_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_10_value_set(preset["value"]);
}

void numberobj_11_init() {
    this->numberobj_11_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-85"), 1, this->_currentTime);
}

void numberobj_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_11_value;
}

void numberobj_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_11_value_set(preset["value"]);
}

void numberobj_12_init() {
    this->numberobj_12_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-144"), 1, this->_currentTime);
}

void numberobj_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_12_value;
}

void numberobj_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_12_value_set(preset["value"]);
}

void numberobj_13_init() {
    this->numberobj_13_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-92"), 1, this->_currentTime);
}

void numberobj_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_13_value;
}

void numberobj_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_13_value_set(preset["value"]);
}

void numberobj_14_init() {
    this->numberobj_14_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-146"), 1, this->_currentTime);
}

void numberobj_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_14_value;
}

void numberobj_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_14_value_set(preset["value"]);
}

void numberobj_15_init() {
    this->numberobj_15_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-89"), 1, this->_currentTime);
}

void numberobj_15_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_15_value;
}

void numberobj_15_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_15_value_set(preset["value"]);
}

void numberobj_16_init() {
    this->numberobj_16_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-148"), 1, this->_currentTime);
}

void numberobj_16_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_16_value;
}

void numberobj_16_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_16_value_set(preset["value"]);
}

void numberobj_17_init() {
    this->numberobj_17_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-107"), 1, this->_currentTime);
}

void numberobj_17_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_17_value;
}

void numberobj_17_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_17_value_set(preset["value"]);
}

void numberobj_18_init() {
    this->numberobj_18_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-149"), 1, this->_currentTime);
}

void numberobj_18_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_18_value;
}

void numberobj_18_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_18_value_set(preset["value"]);
}

void numberobj_19_init() {
    this->numberobj_19_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-102"), 1, this->_currentTime);
}

void numberobj_19_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_19_value;
}

void numberobj_19_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_19_value_set(preset["value"]);
}

void numberobj_20_init() {
    this->numberobj_20_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-151"), 1, this->_currentTime);
}

void numberobj_20_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_20_value;
}

void numberobj_20_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_20_value_set(preset["value"]);
}

void numberobj_21_init() {
    this->numberobj_21_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-99"), 1, this->_currentTime);
}

void numberobj_21_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_21_value;
}

void numberobj_21_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_21_value_set(preset["value"]);
}

void numberobj_22_init() {
    this->numberobj_22_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-153"), 1, this->_currentTime);
}

void numberobj_22_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_22_value;
}

void numberobj_22_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_22_value_set(preset["value"]);
}

void numberobj_23_init() {
    this->numberobj_23_currentFormat = 6;
    this->getEngine()->sendNumMessage(TAG("setup"), TAG("number_obj-95"), 1, this->_currentTime);
}

void numberobj_23_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_23_value;
}

void numberobj_23_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_23_value_set(preset["value"]);
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

void updateTime(MillisecondTime time) {
    this->_currentTime = time;
    this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr)));

    if (this->sampleOffsetIntoNextAudioBuffer >= (SampleIndex)(this->vs))
        this->sampleOffsetIntoNextAudioBuffer = (SampleIndex)(this->vs) - 1;

    if (this->sampleOffsetIntoNextAudioBuffer < 0)
        this->sampleOffsetIntoNextAudioBuffer = 0;
}

void assign_defaults()
{
    delay_01_time = 100;
    delay_01_delayall = 1;
    gaintilde_01_input_number = 0;
    gaintilde_01_value = 0;
    gaintilde_01_interp = 10;
    groove_01_rate_auto = 1;
    groove_01_begin = 0;
    groove_01_end = -1;
    groove_01_loop = 1;
    groove_01_crossfade = 0;
    delay_02_time = 4000;
    delay_02_delayall = 1;
    gaintilde_02_input_number = 0;
    gaintilde_02_value = 0;
    gaintilde_02_interp = 10;
    gaintilde_03_input_number = 0;
    gaintilde_03_value = 0;
    gaintilde_03_interp = 10;
    delay_03_time = 250;
    delay_03_delayall = 1;
    gaintilde_04_input_number = 0;
    gaintilde_04_value = 0;
    gaintilde_04_interp = 10;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    gaintilde_05_input_number = 0;
    gaintilde_05_value = 0;
    gaintilde_05_interp = 10;
    gaintilde_06_input_number = 0;
    gaintilde_06_value = 0;
    gaintilde_06_interp = 10;
    gaintilde_07_input_number = 0;
    gaintilde_07_value = 0;
    gaintilde_07_interp = 10;
    gaintilde_08_input_number = 0;
    gaintilde_08_value = 0;
    gaintilde_08_interp = 10;
    delay_04_time = 500;
    delay_04_delayall = 1;
    toggle_01_value_number = 0;
    toggle_01_value_number_setter(toggle_01_value_number);
    gaintilde_09_input_number = 0;
    gaintilde_09_value = 0;
    gaintilde_09_interp = 10;
    numberobj_02_value = 0;
    numberobj_02_value_setter(numberobj_02_value);
    data_01_sizeout = 0;
    data_01_size = 0;
    data_01_sizems = 0;
    data_01_normalize = 0.995;
    data_01_channels = 1;
    gaintilde_10_input_number = 0;
    gaintilde_10_value = 0;
    gaintilde_10_interp = 10;
    gaintilde_11_input_number = 0;
    gaintilde_11_value = 0;
    gaintilde_11_interp = 10;
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    gaintilde_12_input_number = 0;
    gaintilde_12_value = 0;
    gaintilde_12_interp = 10;
    gaintilde_13_input_number = 0;
    gaintilde_13_value = 0;
    gaintilde_13_interp = 10;
    numberobj_04_value = 0;
    numberobj_04_value_setter(numberobj_04_value);
    gaintilde_14_input_number = 0;
    gaintilde_14_value = 0;
    gaintilde_14_interp = 10;
    numberobj_05_value = 0;
    numberobj_05_value_setter(numberobj_05_value);
    gaintilde_15_input_number = 0;
    gaintilde_15_value = 0;
    gaintilde_15_interp = 10;
    gaintilde_16_input_number = 0;
    gaintilde_16_value = 0;
    gaintilde_16_interp = 10;
    numbertilde_01_input_number = 0;
    numbertilde_01_ramp = 0;
    dspexpr_01_in1 = 0;
    dspexpr_01_in2 = 0.001;
    numberobj_06_value = 0;
    numberobj_06_value_setter(numberobj_06_value);
    numberobj_07_value = 0;
    numberobj_07_value_setter(numberobj_07_value);
    expr_01_in1 = 0;
    expr_01_in2 = 60;
    expr_01_out1 = 0;
    delay_05_time = 2000;
    delay_05_delayall = 1;
    data_02_sizeout = 0;
    data_02_size = 0;
    data_02_sizems = 0;
    data_02_normalize = 0.995;
    data_02_channels = 6;
    scale_01_inlow = 0;
    scale_01_inhigh = 1;
    scale_01_outlow = 0;
    scale_01_outhigh = 150;
    scale_01_power = 1;
    numberobj_08_value = 0;
    numberobj_08_value_setter(numberobj_08_value);
    scale_02_inlow = 0;
    scale_02_inhigh = 150;
    scale_02_outlow = 0;
    scale_02_outhigh = 100;
    scale_02_power = 1;
    numberobj_09_value = 0;
    numberobj_09_value_setter(numberobj_09_value);
    scale_03_inlow = 0;
    scale_03_inhigh = 150;
    scale_03_outlow = 0;
    scale_03_outhigh = 100;
    scale_03_power = 1;
    numberobj_10_value = 0;
    numberobj_10_value_setter(numberobj_10_value);
    scale_04_inlow = 0;
    scale_04_inhigh = 1;
    scale_04_outlow = 0;
    scale_04_outhigh = 150;
    scale_04_power = 1;
    numberobj_11_value = 0;
    numberobj_11_value_setter(numberobj_11_value);
    scale_05_inlow = 0;
    scale_05_inhigh = 150;
    scale_05_outlow = 0;
    scale_05_outhigh = 100;
    scale_05_power = 1;
    numberobj_12_value = 0;
    numberobj_12_value_setter(numberobj_12_value);
    scale_06_inlow = 0;
    scale_06_inhigh = 1;
    scale_06_outlow = 0;
    scale_06_outhigh = 150;
    scale_06_power = 1;
    numberobj_13_value = 0;
    numberobj_13_value_setter(numberobj_13_value);
    scale_07_inlow = 0;
    scale_07_inhigh = 150;
    scale_07_outlow = 0;
    scale_07_outhigh = 100;
    scale_07_power = 1;
    numberobj_14_value = 0;
    numberobj_14_value_setter(numberobj_14_value);
    scale_08_inlow = 0;
    scale_08_inhigh = 1;
    scale_08_outlow = 0;
    scale_08_outhigh = 150;
    scale_08_power = 1;
    numberobj_15_value = 0;
    numberobj_15_value_setter(numberobj_15_value);
    scale_09_inlow = 0;
    scale_09_inhigh = 150;
    scale_09_outlow = 0;
    scale_09_outhigh = 100;
    scale_09_power = 1;
    numberobj_16_value = 0;
    numberobj_16_value_setter(numberobj_16_value);
    scale_10_inlow = 0;
    scale_10_inhigh = 1;
    scale_10_outlow = 0;
    scale_10_outhigh = 150;
    scale_10_power = 1;
    numberobj_17_value = 0;
    numberobj_17_value_setter(numberobj_17_value);
    scale_11_inlow = 0;
    scale_11_inhigh = 150;
    scale_11_outlow = 0;
    scale_11_outhigh = 100;
    scale_11_power = 1;
    numberobj_18_value = 0;
    numberobj_18_value_setter(numberobj_18_value);
    scale_12_inlow = 0;
    scale_12_inhigh = 1;
    scale_12_outlow = 0;
    scale_12_outhigh = 150;
    scale_12_power = 1;
    numberobj_19_value = 0;
    numberobj_19_value_setter(numberobj_19_value);
    scale_13_inlow = 0;
    scale_13_inhigh = 150;
    scale_13_outlow = 0;
    scale_13_outhigh = 100;
    scale_13_power = 1;
    numberobj_20_value = 0;
    numberobj_20_value_setter(numberobj_20_value);
    scale_14_inlow = 0;
    scale_14_inhigh = 1;
    scale_14_outlow = 0;
    scale_14_outhigh = 150;
    scale_14_power = 1;
    numberobj_21_value = 0;
    numberobj_21_value_setter(numberobj_21_value);
    scale_15_inlow = 0;
    scale_15_inhigh = 150;
    scale_15_outlow = 0;
    scale_15_outhigh = 100;
    scale_15_power = 1;
    numberobj_22_value = 0;
    numberobj_22_value_setter(numberobj_22_value);
    scale_16_inlow = 0;
    scale_16_inhigh = 1;
    scale_16_outlow = 0;
    scale_16_outhigh = 150;
    scale_16_power = 1;
    numberobj_23_value = 0;
    numberobj_23_value_setter(numberobj_23_value);
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.00002267573696;
    gaintilde_01_lastValue = 0;
    gaintilde_01_loginc = 1;
    gaintilde_01_zval = 0;
    gaintilde_01_ramp_d_prev = 0;
    gaintilde_01_ramp_prev = 0;
    gaintilde_01_ramp_index = 0;
    gaintilde_01_ramp_increment = 0;
    gaintilde_01_setupDone = false;
    groove_01_readIndex = 0;
    groove_01_playStatus = 0;
    groove_01_changeIncomingInSamples = 0;
    groove_01_incomingChange = 2;
    groove_01_crossfadeInSamples = 0;
    groove_01_setupDone = false;
    gaintilde_02_lastValue = 0;
    gaintilde_02_loginc = 1;
    gaintilde_02_zval = 0;
    gaintilde_02_ramp_d_prev = 0;
    gaintilde_02_ramp_prev = 0;
    gaintilde_02_ramp_index = 0;
    gaintilde_02_ramp_increment = 0;
    gaintilde_02_setupDone = false;
    gaintilde_03_lastValue = 0;
    gaintilde_03_loginc = 1;
    gaintilde_03_zval = 0;
    gaintilde_03_ramp_d_prev = 0;
    gaintilde_03_ramp_prev = 0;
    gaintilde_03_ramp_index = 0;
    gaintilde_03_ramp_increment = 0;
    gaintilde_03_setupDone = false;
    gaintilde_04_lastValue = 0;
    gaintilde_04_loginc = 1;
    gaintilde_04_zval = 0;
    gaintilde_04_ramp_d_prev = 0;
    gaintilde_04_ramp_prev = 0;
    gaintilde_04_ramp_index = 0;
    gaintilde_04_ramp_increment = 0;
    gaintilde_04_setupDone = false;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    gaintilde_05_lastValue = 0;
    gaintilde_05_loginc = 1;
    gaintilde_05_zval = 0;
    gaintilde_05_ramp_d_prev = 0;
    gaintilde_05_ramp_prev = 0;
    gaintilde_05_ramp_index = 0;
    gaintilde_05_ramp_increment = 0;
    gaintilde_05_setupDone = false;
    gaintilde_06_lastValue = 0;
    gaintilde_06_loginc = 1;
    gaintilde_06_zval = 0;
    gaintilde_06_ramp_d_prev = 0;
    gaintilde_06_ramp_prev = 0;
    gaintilde_06_ramp_index = 0;
    gaintilde_06_ramp_increment = 0;
    gaintilde_06_setupDone = false;
    gaintilde_07_lastValue = 0;
    gaintilde_07_loginc = 1;
    gaintilde_07_zval = 0;
    gaintilde_07_ramp_d_prev = 0;
    gaintilde_07_ramp_prev = 0;
    gaintilde_07_ramp_index = 0;
    gaintilde_07_ramp_increment = 0;
    gaintilde_07_setupDone = false;
    gaintilde_08_lastValue = 0;
    gaintilde_08_loginc = 1;
    gaintilde_08_zval = 0;
    gaintilde_08_ramp_d_prev = 0;
    gaintilde_08_ramp_prev = 0;
    gaintilde_08_ramp_index = 0;
    gaintilde_08_ramp_increment = 0;
    gaintilde_08_setupDone = false;
    toggle_01_lastValue = 0;
    gaintilde_09_lastValue = 0;
    gaintilde_09_loginc = 1;
    gaintilde_09_zval = 0;
    gaintilde_09_ramp_d_prev = 0;
    gaintilde_09_ramp_prev = 0;
    gaintilde_09_ramp_index = 0;
    gaintilde_09_ramp_increment = 0;
    gaintilde_09_setupDone = false;
    numberobj_02_currentFormat = 6;
    numberobj_02_lastValue = 0;
    data_01_sizemode = 0;
    data_01_setupDone = false;
    gaintilde_10_lastValue = 0;
    gaintilde_10_loginc = 1;
    gaintilde_10_zval = 0;
    gaintilde_10_ramp_d_prev = 0;
    gaintilde_10_ramp_prev = 0;
    gaintilde_10_ramp_index = 0;
    gaintilde_10_ramp_increment = 0;
    gaintilde_10_setupDone = false;
    gaintilde_11_lastValue = 0;
    gaintilde_11_loginc = 1;
    gaintilde_11_zval = 0;
    gaintilde_11_ramp_d_prev = 0;
    gaintilde_11_ramp_prev = 0;
    gaintilde_11_ramp_index = 0;
    gaintilde_11_ramp_increment = 0;
    gaintilde_11_setupDone = false;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    gaintilde_12_lastValue = 0;
    gaintilde_12_loginc = 1;
    gaintilde_12_zval = 0;
    gaintilde_12_ramp_d_prev = 0;
    gaintilde_12_ramp_prev = 0;
    gaintilde_12_ramp_index = 0;
    gaintilde_12_ramp_increment = 0;
    gaintilde_12_setupDone = false;
    gaintilde_13_lastValue = 0;
    gaintilde_13_loginc = 1;
    gaintilde_13_zval = 0;
    gaintilde_13_ramp_d_prev = 0;
    gaintilde_13_ramp_prev = 0;
    gaintilde_13_ramp_index = 0;
    gaintilde_13_ramp_increment = 0;
    gaintilde_13_setupDone = false;
    numberobj_04_currentFormat = 6;
    numberobj_04_lastValue = 0;
    gaintilde_14_lastValue = 0;
    gaintilde_14_loginc = 1;
    gaintilde_14_zval = 0;
    gaintilde_14_ramp_d_prev = 0;
    gaintilde_14_ramp_prev = 0;
    gaintilde_14_ramp_index = 0;
    gaintilde_14_ramp_increment = 0;
    gaintilde_14_setupDone = false;
    numberobj_05_currentFormat = 6;
    numberobj_05_lastValue = 0;
    gaintilde_15_lastValue = 0;
    gaintilde_15_loginc = 1;
    gaintilde_15_zval = 0;
    gaintilde_15_ramp_d_prev = 0;
    gaintilde_15_ramp_prev = 0;
    gaintilde_15_ramp_index = 0;
    gaintilde_15_ramp_increment = 0;
    gaintilde_15_setupDone = false;
    gaintilde_16_lastValue = 0;
    gaintilde_16_loginc = 1;
    gaintilde_16_zval = 0;
    gaintilde_16_ramp_d_prev = 0;
    gaintilde_16_ramp_prev = 0;
    gaintilde_16_ramp_index = 0;
    gaintilde_16_ramp_increment = 0;
    gaintilde_16_setupDone = false;
    numbertilde_01_currentInterval = 0;
    numbertilde_01_currentIntervalInSamples = 0;
    numbertilde_01_lastValue = 0;
    numbertilde_01_outValue = 0;
    numbertilde_01_rampInSamples = 0;
    numbertilde_01_currentMode = 0;
    numbertilde_01_smooth_d_prev = 0;
    numbertilde_01_smooth_prev = 0;
    numbertilde_01_smooth_index = 0;
    numbertilde_01_smooth_increment = 0;
    numbertilde_01_setupDone = false;
    numberobj_06_currentFormat = 6;
    numberobj_06_lastValue = 0;
    numberobj_07_currentFormat = 6;
    numberobj_07_lastValue = 0;
    data_02_sizemode = 0;
    data_02_setupDone = false;
    numberobj_08_currentFormat = 6;
    numberobj_08_lastValue = 0;
    numberobj_09_currentFormat = 6;
    numberobj_09_lastValue = 0;
    numberobj_10_currentFormat = 6;
    numberobj_10_lastValue = 0;
    numberobj_11_currentFormat = 6;
    numberobj_11_lastValue = 0;
    numberobj_12_currentFormat = 6;
    numberobj_12_lastValue = 0;
    numberobj_13_currentFormat = 6;
    numberobj_13_lastValue = 0;
    numberobj_14_currentFormat = 6;
    numberobj_14_lastValue = 0;
    numberobj_15_currentFormat = 6;
    numberobj_15_lastValue = 0;
    numberobj_16_currentFormat = 6;
    numberobj_16_lastValue = 0;
    numberobj_17_currentFormat = 6;
    numberobj_17_lastValue = 0;
    numberobj_18_currentFormat = 6;
    numberobj_18_lastValue = 0;
    numberobj_19_currentFormat = 6;
    numberobj_19_lastValue = 0;
    numberobj_20_currentFormat = 6;
    numberobj_20_lastValue = 0;
    numberobj_21_currentFormat = 6;
    numberobj_21_lastValue = 0;
    numberobj_22_currentFormat = 6;
    numberobj_22_lastValue = 0;
    numberobj_23_currentFormat = 6;
    numberobj_23_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number delay_01_time;
    number delay_01_delayall;
    number gaintilde_01_input_number;
    number gaintilde_01_value;
    number gaintilde_01_interp;
    number groove_01_rate_auto;
    number groove_01_begin;
    number groove_01_end;
    number groove_01_loop;
    number groove_01_crossfade;
    number delay_02_time;
    number delay_02_delayall;
    number gaintilde_02_input_number;
    number gaintilde_02_value;
    number gaintilde_02_interp;
    number gaintilde_03_input_number;
    number gaintilde_03_value;
    number gaintilde_03_interp;
    number delay_03_time;
    number delay_03_delayall;
    number gaintilde_04_input_number;
    number gaintilde_04_value;
    number gaintilde_04_interp;
    number numberobj_01_value;
    list message_01_set;
    number gaintilde_05_input_number;
    number gaintilde_05_value;
    number gaintilde_05_interp;
    number gaintilde_06_input_number;
    number gaintilde_06_value;
    number gaintilde_06_interp;
    number gaintilde_07_input_number;
    number gaintilde_07_value;
    number gaintilde_07_interp;
    number gaintilde_08_input_number;
    number gaintilde_08_value;
    number gaintilde_08_interp;
    number delay_04_time;
    number delay_04_delayall;
    number toggle_01_value_number;
    number gaintilde_09_input_number;
    number gaintilde_09_value;
    number gaintilde_09_interp;
    number numberobj_02_value;
    number data_01_sizeout;
    number data_01_size;
    number data_01_sizems;
    number data_01_normalize;
    number data_01_channels;
    number gaintilde_10_input_number;
    number gaintilde_10_value;
    number gaintilde_10_interp;
    number gaintilde_11_input_number;
    number gaintilde_11_value;
    number gaintilde_11_interp;
    number numberobj_03_value;
    number gaintilde_12_input_number;
    number gaintilde_12_value;
    number gaintilde_12_interp;
    number gaintilde_13_input_number;
    number gaintilde_13_value;
    number gaintilde_13_interp;
    number numberobj_04_value;
    number gaintilde_14_input_number;
    number gaintilde_14_value;
    number gaintilde_14_interp;
    number numberobj_05_value;
    number gaintilde_15_input_number;
    number gaintilde_15_value;
    number gaintilde_15_interp;
    number gaintilde_16_input_number;
    number gaintilde_16_value;
    number gaintilde_16_interp;
    number numbertilde_01_input_number;
    number numbertilde_01_ramp;
    number dspexpr_01_in1;
    number dspexpr_01_in2;
    number numberobj_06_value;
    number numberobj_07_value;
    number expr_01_in1;
    number expr_01_in2;
    number expr_01_out1;
    number delay_05_time;
    number delay_05_delayall;
    list message_02_set;
    number data_02_sizeout;
    number data_02_size;
    number data_02_sizems;
    number data_02_normalize;
    number data_02_channels;
    list scale_01_input;
    number scale_01_inlow;
    number scale_01_inhigh;
    number scale_01_outlow;
    number scale_01_outhigh;
    number scale_01_power;
    list scale_01_out;
    number numberobj_08_value;
    list scale_02_input;
    number scale_02_inlow;
    number scale_02_inhigh;
    number scale_02_outlow;
    number scale_02_outhigh;
    number scale_02_power;
    list scale_02_out;
    number numberobj_09_value;
    list scale_03_input;
    number scale_03_inlow;
    number scale_03_inhigh;
    number scale_03_outlow;
    number scale_03_outhigh;
    number scale_03_power;
    list scale_03_out;
    number numberobj_10_value;
    list scale_04_input;
    number scale_04_inlow;
    number scale_04_inhigh;
    number scale_04_outlow;
    number scale_04_outhigh;
    number scale_04_power;
    list scale_04_out;
    number numberobj_11_value;
    list scale_05_input;
    number scale_05_inlow;
    number scale_05_inhigh;
    number scale_05_outlow;
    number scale_05_outhigh;
    number scale_05_power;
    list scale_05_out;
    number numberobj_12_value;
    list scale_06_input;
    number scale_06_inlow;
    number scale_06_inhigh;
    number scale_06_outlow;
    number scale_06_outhigh;
    number scale_06_power;
    list scale_06_out;
    number numberobj_13_value;
    list scale_07_input;
    number scale_07_inlow;
    number scale_07_inhigh;
    number scale_07_outlow;
    number scale_07_outhigh;
    number scale_07_power;
    list scale_07_out;
    number numberobj_14_value;
    list scale_08_input;
    number scale_08_inlow;
    number scale_08_inhigh;
    number scale_08_outlow;
    number scale_08_outhigh;
    number scale_08_power;
    list scale_08_out;
    number numberobj_15_value;
    list scale_09_input;
    number scale_09_inlow;
    number scale_09_inhigh;
    number scale_09_outlow;
    number scale_09_outhigh;
    number scale_09_power;
    list scale_09_out;
    number numberobj_16_value;
    list scale_10_input;
    number scale_10_inlow;
    number scale_10_inhigh;
    number scale_10_outlow;
    number scale_10_outhigh;
    number scale_10_power;
    list scale_10_out;
    number numberobj_17_value;
    list scale_11_input;
    number scale_11_inlow;
    number scale_11_inhigh;
    number scale_11_outlow;
    number scale_11_outhigh;
    number scale_11_power;
    list scale_11_out;
    number numberobj_18_value;
    list scale_12_input;
    number scale_12_inlow;
    number scale_12_inhigh;
    number scale_12_outlow;
    number scale_12_outhigh;
    number scale_12_power;
    list scale_12_out;
    number numberobj_19_value;
    list scale_13_input;
    number scale_13_inlow;
    number scale_13_inhigh;
    number scale_13_outlow;
    number scale_13_outhigh;
    number scale_13_power;
    list scale_13_out;
    number numberobj_20_value;
    list scale_14_input;
    number scale_14_inlow;
    number scale_14_inhigh;
    number scale_14_outlow;
    number scale_14_outhigh;
    number scale_14_power;
    list scale_14_out;
    number numberobj_21_value;
    list scale_15_input;
    number scale_15_inlow;
    number scale_15_inhigh;
    number scale_15_outlow;
    number scale_15_outhigh;
    number scale_15_power;
    list scale_15_out;
    number numberobj_22_value;
    list scale_16_input;
    number scale_16_inlow;
    number scale_16_inhigh;
    number scale_16_outlow;
    number scale_16_outhigh;
    number scale_16_power;
    list scale_16_out;
    number numberobj_23_value;
    MillisecondTime _currentTime;
    UInt64 audioProcessSampleCount;
    SampleIndex sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[2];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number gaintilde_01_lastValue;
    number gaintilde_01_loginc;
    number gaintilde_01_zval;
    number gaintilde_01_ramp_d_prev;
    number gaintilde_01_ramp_prev;
    number gaintilde_01_ramp_index;
    number gaintilde_01_ramp_increment;
    bool gaintilde_01_setupDone;
    Float32BufferRef groove_01_buffer;
    number groove_01_readIndex;
    Index groove_01_playStatus;
    SampleIndex groove_01_changeIncomingInSamples;
    Int groove_01_incomingChange;
    SampleIndex groove_01_crossfadeInSamples;
    bool groove_01_setupDone;
    number gaintilde_02_lastValue;
    number gaintilde_02_loginc;
    number gaintilde_02_zval;
    number gaintilde_02_ramp_d_prev;
    number gaintilde_02_ramp_prev;
    number gaintilde_02_ramp_index;
    number gaintilde_02_ramp_increment;
    bool gaintilde_02_setupDone;
    number gaintilde_03_lastValue;
    number gaintilde_03_loginc;
    number gaintilde_03_zval;
    number gaintilde_03_ramp_d_prev;
    number gaintilde_03_ramp_prev;
    number gaintilde_03_ramp_index;
    number gaintilde_03_ramp_increment;
    bool gaintilde_03_setupDone;
    number gaintilde_04_lastValue;
    number gaintilde_04_loginc;
    number gaintilde_04_zval;
    number gaintilde_04_ramp_d_prev;
    number gaintilde_04_ramp_prev;
    number gaintilde_04_ramp_index;
    number gaintilde_04_ramp_increment;
    bool gaintilde_04_setupDone;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    number gaintilde_05_lastValue;
    number gaintilde_05_loginc;
    number gaintilde_05_zval;
    number gaintilde_05_ramp_d_prev;
    number gaintilde_05_ramp_prev;
    number gaintilde_05_ramp_index;
    number gaintilde_05_ramp_increment;
    bool gaintilde_05_setupDone;
    number gaintilde_06_lastValue;
    number gaintilde_06_loginc;
    number gaintilde_06_zval;
    number gaintilde_06_ramp_d_prev;
    number gaintilde_06_ramp_prev;
    number gaintilde_06_ramp_index;
    number gaintilde_06_ramp_increment;
    bool gaintilde_06_setupDone;
    number gaintilde_07_lastValue;
    number gaintilde_07_loginc;
    number gaintilde_07_zval;
    number gaintilde_07_ramp_d_prev;
    number gaintilde_07_ramp_prev;
    number gaintilde_07_ramp_index;
    number gaintilde_07_ramp_increment;
    bool gaintilde_07_setupDone;
    number gaintilde_08_lastValue;
    number gaintilde_08_loginc;
    number gaintilde_08_zval;
    number gaintilde_08_ramp_d_prev;
    number gaintilde_08_ramp_prev;
    number gaintilde_08_ramp_index;
    number gaintilde_08_ramp_increment;
    bool gaintilde_08_setupDone;
    number toggle_01_lastValue;
    number gaintilde_09_lastValue;
    number gaintilde_09_loginc;
    number gaintilde_09_zval;
    number gaintilde_09_ramp_d_prev;
    number gaintilde_09_ramp_prev;
    number gaintilde_09_ramp_index;
    number gaintilde_09_ramp_increment;
    bool gaintilde_09_setupDone;
    Int numberobj_02_currentFormat;
    number numberobj_02_lastValue;
    Float32BufferRef data_01_buffer;
    Int data_01_sizemode;
    bool data_01_setupDone;
    number gaintilde_10_lastValue;
    number gaintilde_10_loginc;
    number gaintilde_10_zval;
    number gaintilde_10_ramp_d_prev;
    number gaintilde_10_ramp_prev;
    number gaintilde_10_ramp_index;
    number gaintilde_10_ramp_increment;
    bool gaintilde_10_setupDone;
    number gaintilde_11_lastValue;
    number gaintilde_11_loginc;
    number gaintilde_11_zval;
    number gaintilde_11_ramp_d_prev;
    number gaintilde_11_ramp_prev;
    number gaintilde_11_ramp_index;
    number gaintilde_11_ramp_increment;
    bool gaintilde_11_setupDone;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    number gaintilde_12_lastValue;
    number gaintilde_12_loginc;
    number gaintilde_12_zval;
    number gaintilde_12_ramp_d_prev;
    number gaintilde_12_ramp_prev;
    number gaintilde_12_ramp_index;
    number gaintilde_12_ramp_increment;
    bool gaintilde_12_setupDone;
    number gaintilde_13_lastValue;
    number gaintilde_13_loginc;
    number gaintilde_13_zval;
    number gaintilde_13_ramp_d_prev;
    number gaintilde_13_ramp_prev;
    number gaintilde_13_ramp_index;
    number gaintilde_13_ramp_increment;
    bool gaintilde_13_setupDone;
    Int numberobj_04_currentFormat;
    number numberobj_04_lastValue;
    number gaintilde_14_lastValue;
    number gaintilde_14_loginc;
    number gaintilde_14_zval;
    number gaintilde_14_ramp_d_prev;
    number gaintilde_14_ramp_prev;
    number gaintilde_14_ramp_index;
    number gaintilde_14_ramp_increment;
    bool gaintilde_14_setupDone;
    Int numberobj_05_currentFormat;
    number numberobj_05_lastValue;
    number gaintilde_15_lastValue;
    number gaintilde_15_loginc;
    number gaintilde_15_zval;
    number gaintilde_15_ramp_d_prev;
    number gaintilde_15_ramp_prev;
    number gaintilde_15_ramp_index;
    number gaintilde_15_ramp_increment;
    bool gaintilde_15_setupDone;
    number gaintilde_16_lastValue;
    number gaintilde_16_loginc;
    number gaintilde_16_zval;
    number gaintilde_16_ramp_d_prev;
    number gaintilde_16_ramp_prev;
    number gaintilde_16_ramp_index;
    number gaintilde_16_ramp_increment;
    bool gaintilde_16_setupDone;
    SampleIndex numbertilde_01_currentInterval;
    SampleIndex numbertilde_01_currentIntervalInSamples;
    number numbertilde_01_lastValue;
    number numbertilde_01_outValue;
    number numbertilde_01_rampInSamples;
    Int numbertilde_01_currentMode;
    number numbertilde_01_smooth_d_prev;
    number numbertilde_01_smooth_prev;
    number numbertilde_01_smooth_index;
    number numbertilde_01_smooth_increment;
    bool numbertilde_01_setupDone;
    Int numberobj_06_currentFormat;
    number numberobj_06_lastValue;
    Int numberobj_07_currentFormat;
    number numberobj_07_lastValue;
    Float32BufferRef data_02_buffer;
    Int data_02_sizemode;
    bool data_02_setupDone;
    Int numberobj_08_currentFormat;
    number numberobj_08_lastValue;
    Int numberobj_09_currentFormat;
    number numberobj_09_lastValue;
    Int numberobj_10_currentFormat;
    number numberobj_10_lastValue;
    Int numberobj_11_currentFormat;
    number numberobj_11_lastValue;
    Int numberobj_12_currentFormat;
    number numberobj_12_lastValue;
    Int numberobj_13_currentFormat;
    number numberobj_13_lastValue;
    Int numberobj_14_currentFormat;
    number numberobj_14_lastValue;
    Int numberobj_15_currentFormat;
    number numberobj_15_lastValue;
    Int numberobj_16_currentFormat;
    number numberobj_16_lastValue;
    Int numberobj_17_currentFormat;
    number numberobj_17_lastValue;
    Int numberobj_18_currentFormat;
    number numberobj_18_lastValue;
    Int numberobj_19_currentFormat;
    number numberobj_19_lastValue;
    Int numberobj_20_currentFormat;
    number numberobj_20_lastValue;
    Int numberobj_21_currentFormat;
    number numberobj_21_lastValue;
    Int numberobj_22_currentFormat;
    number numberobj_22_lastValue;
    Int numberobj_23_currentFormat;
    number numberobj_23_lastValue;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef playback;
    DataRef b_audio_wav;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;

};

PatcherInterface* creaternbomatic()
{
    return new rnbomatic();
}

#ifndef RNBO_NO_PATCHERFACTORY

extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction(PlatformInterface* platformInterface)
#else

extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction(PlatformInterface* platformInterface)
#endif

{
    Platform::set(platformInterface);
    return creaternbomatic;
}

} // end RNBO namespace

