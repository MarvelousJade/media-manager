#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <cstdint>

namespace seneca 
{
    struct Settings 
    {
        int16_t m_maxSummaryWidth;
        bool m_tableView;
    };

    extern Settings g_settings;
}

#endif

