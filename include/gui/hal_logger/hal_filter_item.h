//  MIT License
//
//  Copyright (c) 2019 Ruhr-University Bochum, Germany, Chair for Embedded Security. All Rights reserved.
//  Copyright (c) 2019 Marc Fyrbiak, Sebastian Wallat, Max Hoffmann ("ORIGINAL AUTHORS"). All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#ifndef HAL_FILTER_ITEM_H
#define HAL_FILTER_ITEM_H

#include <QList>
#include <QRegularExpression>

struct hal_filter_item
{
    enum class rule
    {
        ShowAll = 0,
        HideAll = 1,
        Process = 2
    };

    hal_filter_item(rule trace, rule debug, rule info, rule warning, rule error, rule critical, rule default_rule, QStringList& keywords, QRegularExpression& reg_ex)
        : m_trace(trace), m_debug(debug), m_info(info), m_warning(warning), m_error(error), m_critical(critical), m_default(default_rule), m_keywords(keywords), m_reg_ex(reg_ex)
    {
    }

    const rule m_trace;

    const rule m_debug;

    const rule m_info;

    const rule m_warning;

    const rule m_error;

    const rule m_critical;

    const rule m_default;

    const QStringList m_keywords;

    const QRegularExpression m_reg_ex;
};

#endif    // HAL_FILTER_ITEM_H
