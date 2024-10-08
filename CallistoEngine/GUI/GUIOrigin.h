#pragma once

enum class GUIOrigin : unsigned char
{
    _TOP = 1,
    _BOTTOM = 1 << 1,
    _LEFT = 1 << 2,
    _RIGHT = 1 << 3,
    _V_CENTRE = 1 << 4,
    _H_CENTRE = 1 << 5,

    TOP_LEFT = static_cast<unsigned char>(GUIOrigin::_LEFT) | static_cast<unsigned char>(GUIOrigin::_TOP),
    TOP_CENTRE = static_cast<unsigned char>(GUIOrigin::_H_CENTRE) | static_cast<unsigned char>(GUIOrigin::_TOP),
    TOP_RIGHT = static_cast<unsigned char>(GUIOrigin::_RIGHT) | static_cast<unsigned char>(GUIOrigin::_TOP),

    CENTRE_LEFT = static_cast<unsigned char>(GUIOrigin::_LEFT) | static_cast<unsigned char>(GUIOrigin::_V_CENTRE),
    CENTRE_CENTRE = static_cast<unsigned char>(GUIOrigin::_H_CENTRE) | static_cast<unsigned char>(GUIOrigin::_V_CENTRE),
    CENTRE_RIGHT = static_cast<unsigned char>(GUIOrigin::_RIGHT) | static_cast<unsigned char>(GUIOrigin::_V_CENTRE),

    BOTTOM_LEFT = static_cast<unsigned char>(GUIOrigin::_LEFT) | static_cast<unsigned char>(GUIOrigin::_BOTTOM),
    BOTTOM_CENTRE = static_cast<unsigned char>(GUIOrigin::_H_CENTRE) | static_cast<unsigned char>(GUIOrigin::_BOTTOM),
    BOTTOM_RIGHT = static_cast<unsigned char>(GUIOrigin::_RIGHT) | static_cast<unsigned char>(GUIOrigin::_BOTTOM),
};