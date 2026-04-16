#include "led.h"

void Led::turn_on()
{
    m_state = true;
    if (m_pin != 0xFF) {
        digitalWrite(m_pin, m_reverse_logic ? !m_state : m_state);
    }
}

void Led::turn_off()
{
    m_state = false;
    if (m_pin != 0xFF) {
        digitalWrite(m_pin, m_reverse_logic ? !m_state : m_state);
    }
}

void Led::set(bool state)
{
    m_state = state;
    if (m_pin != 0xFF) {
        digitalWrite(m_pin, m_reverse_logic ? !state : state);
    }
}

bool Led::get()
{
    return m_state;
}
