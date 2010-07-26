/**
 * @file dlgprefsound.h
 * @author Bill Good <bkgood at gmail dot com>
 * @date 20100625
 */

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DLGPREFSOUND_H
#define DLGPREFSOUND_H

#include <QtCore>
#include "ui_dlgprefsounddlg.h"
#include "configobject.h"
#include "soundmanagerconfig.h"

class SoundManager;
class ControlObject;
class SoundDevice;

const unsigned int NUM_DECKS = 2; // this is temporary... eventually this shoud come from
                                  // soundmanager or something

class DlgPrefSound : public QWidget, public Ui::DlgPrefSoundDlg  {
    Q_OBJECT;
public:
    DlgPrefSound(QWidget *parent, SoundManager *soundManager,
            ConfigObject<ConfigValue> *config);
    ~DlgPrefSound();
signals:
    void loadPaths(const SoundManagerConfig &config);
    void writePaths(SoundManagerConfig *config);
    void refreshOutputDevices(const QList<SoundDevice*> &devices);
    void refreshInputDevices(const QList<SoundDevice*> &devices);
public slots:
    void slotUpdate(); // called on show
    void slotApply();  // called on ok button
    void forceApply(); // called by DlgPrefVinyl to make slotApply call setupDevices
private:
    void initializePaths();
    void loadSettings();
    SoundManager *m_pSoundManager;
    ConfigObject<ConfigValue> *m_pConfig;
    QList<SoundDevice*> m_inputDevices;
    QList<SoundDevice*> m_outputDevices;
    bool m_settingsModified;
    SoundManagerConfig m_config;
    bool m_loading;
    bool m_forceApply;
private slots:
    void apiChanged(int index);
    void sampleRateChanged(int index);
    void latencyChanged(int index);
    void updateLatencies(int sampleRateIndex);
    void refreshDevices();
    void settingChanged();
};

#endif
