//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2021 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#ifndef MU_UI_WINDOWSPLATFORMTHEME_H
#define MU_UI_WINDOWSPLATFORMTHEME_H

#include "iplatformtheme.h"

#include "modularity/ioc.h"
#include "async/asyncable.h"
#include "iuiconfiguration.h"

namespace mu::ui {
class WindowsPlatformTheme : public IPlatformTheme, public async::Asyncable
{
    INJECT(ui, IUiConfiguration, configuration)

public:
    WindowsPlatformTheme();
    ~WindowsPlatformTheme();

    void init() override;

    bool isFollowSystemThemeAvailable() const override;

    bool isDarkMode() const override;
    async::Channel<bool> darkModeSwitched() const override;

    void setAppThemeDark(bool) override;
    void styleWindow(QWidget*) override;

private:
    async::Channel<bool> m_darkModeSwitched;
    int m_buildNumber = 0;
    std::atomic<bool> m_isListening = false;
    std::thread m_listenThread;
    void updateListeningStatus(IUiConfiguration::ThemeType themeType);
    void startListening();
    void th_listen();
    void stopListening();
};
}

#endif // MU_UI_WINDOWSPLATFORMTHEME_H
