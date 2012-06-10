#include "melodynote.h"

MelodyNote::MelodyNote()
    : Symbol()
{
    m_dots = 0;
    m_pitch = new Pitch();
}

void MelodyNote::addDot()
{
    m_dots++;
    m_dots = m_dots > 2 ? 0 : m_dots;
}

int MelodyNote::dots() const
{
    return m_dots;
}

void MelodyNote::setDots(int dots)
{
    if( dots < 0 )
        m_dots = 0;
    else if( dots > 2 )
        m_dots = 2;
    else
        m_dots = dots;
}

QStandardItem *MelodyNote::pitch() const
{
    return m_pitch;
}

MelodyNote::~MelodyNote()
{
    delete m_pitch;
}
