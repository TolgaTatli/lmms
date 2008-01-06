/*
 * mallets.h - tuned instruments that one would bang upon
 *
 * Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
 * 
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _MALLET_H
#define _MALLET_H

#include "Instrmnt.h"

#include "combobox.h"
#include "instrument.h"
#include "instrument_view.h"
#include "knob.h"
#include "note_play_handle.h"
#include "led_checkbox.h"


class malletsSynth
{
public:
	// ModalBar
	malletsSynth( const StkFloat _pitch,
			const StkFloat _velocity,
			const StkFloat _control1,
			const StkFloat _control2,
			const StkFloat _control4,
			const StkFloat _control8,
			const StkFloat _control11,
			const int _control16,
			const Uint8 _delay,
			const sample_rate_t _sample_rate );

	// TubeBell
	malletsSynth( const StkFloat _pitch,
			const StkFloat _velocity,
			const int _preset,
			const StkFloat _control1,
			const StkFloat _control2,
			const StkFloat _control4,
			const StkFloat _control11,
			const StkFloat _control128,
			const Uint8 _delay,
			const sample_rate_t _sample_rate );

	// BandedWG
	malletsSynth( const StkFloat _pitch,
			const StkFloat _velocity,
			const StkFloat _control2,
			const StkFloat _control4,
			const StkFloat _control11,
			const int _control16,
			const StkFloat _control64,
			const StkFloat _control128,
			const Uint8 _delay,
			const sample_rate_t _sample_rate );

	inline ~malletsSynth( void )
	{
		m_voice->noteOff( 0.0 );
		delete[] m_delay;
		delete m_voice;
	}

	inline sample_t nextSampleLeft( void )
	{
		if( m_voice == NULL )
		{
			return( 0.0f );
		}
		else
		{
			StkFloat s = m_voice->tick();
			m_delay[m_delayWrite] = s;
			m_delayWrite++;
			return( s );
		}
	}
	
	inline sample_t nextSampleRight( void )
	{
		StkFloat s = m_delay[m_delayRead];
		m_delayRead++;
		return( s );
	}


protected:
	Instrmnt * m_voice;

	StkFloat * m_delay;
	Uint8 m_delayRead;
	Uint8 m_delayWrite;
};




class malletsInstrument : public instrument
{
public:
	malletsInstrument( instrumentTrack * _channel_track );
	virtual ~malletsInstrument( void );

	virtual void FASTCALL playNote( notePlayHandle * _n,
						bool _try_parallelizing );
	virtual void FASTCALL deleteNotePluginData( notePlayHandle * _n );


	virtual void FASTCALL saveSettings( QDomDocument & _doc,
							QDomElement & _parent );
	virtual void FASTCALL loadSettings( const QDomElement & _this );

	virtual QString nodeName( void ) const;

	virtual pluginView * instantiateView( QWidget * _parent );

private:
	knobModel m_hardnessModel;
	knobModel m_positionModel;
	knobModel m_vibratoGainModel;
	knobModel m_vibratoFreqModel;
	knobModel m_stickModel;

	knobModel m_modulatorModel;
	knobModel m_crossfadeModel;
	knobModel m_lfoSpeedModel;
	knobModel m_lfoDepthModel;
	knobModel m_adsrModel;

	knobModel m_pressureModel;
	knobModel m_motionModel;
	knobModel m_vibratoModel;
	knobModel m_velocityModel;

	boolModel m_strikeModel;

	comboBoxModel m_presetsModel;
	knobModel m_spreadModel;

	QVector<sample_t> m_scalers;
	sampleFrame * m_buffer;

	bool m_filesMissing;


	friend class malletsInstrumentView;

} ;


class malletsInstrumentView: public instrumentView
{
	Q_OBJECT
public:
	malletsInstrumentView( malletsInstrument * _instrument,
				QWidget * _parent );
	virtual ~malletsInstrumentView( void );

public slots:
	void changePreset( void );

private:
	virtual void modelChanged( void );

	void setWidgetBackground( QWidget * _widget, const QString & _pic );
	QWidget * setupModalBarControls( QWidget * _parent );
	QWidget * setupTubeBellControls( QWidget * _parent );
	QWidget * setupBandedWGControls( QWidget * _parent );

	QWidget * m_modalBarWidget;
	knob * m_hardnessKnob;
	knob * m_positionKnob;
	knob * m_vibratoGainKnob;
	knob * m_vibratoFreqKnob;
	knob * m_stickKnob;

	QWidget * m_tubeBellWidget;
	knob * m_modulatorKnob;
	knob * m_crossfadeKnob;
	knob * m_lfoSpeedKnob;
	knob * m_lfoDepthKnob;
	knob * m_adsrKnob;

	QWidget * m_bandedWGWidget;
	knob * m_pressureKnob;
	knob * m_motionKnob;
	knob * m_vibratoKnob;
	knob * m_velocityKnob;
	ledCheckBox * m_strikeLED;

	comboBox * m_presetsCombo;
	knob * m_spreadKnob;
};

#endif
