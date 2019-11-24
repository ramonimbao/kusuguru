/* Copyright 2019 Ramon Imbao
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define XXX KC_NO

#define LAYOUT( \
        k00, k01, k02, k03, k04, k05, k06,      k08,      k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h, \
        k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, \
        k20,  k22, k23, k24, k25, k26,     k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h, \
        k30,   k32, k33, k34, k35, k36,                    k3a, k3b, k3c, k3d, k3e, k3f, k3g, \
        k40,     k42, k43, k44, k45, k46,       k48,    k4a, k4b, k4c, k4d, k4e, k4f, k4g, k4h, \
        k50, k51,  k53,       k55,         k57, k58, k59,     k5b,     k5d,      k5f, k5g, k5h \
    ) \
    { \
        {k00, k01, k02, k03, k04, k05, k06, XXX, k08, XXX, k0a, k0b, k0c, k0d, k0e, k0f, k0g, k0h}, \
        {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h}, \
        {k20, XXX, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, k2g, k2h}, \
        {k30, XXX, k32, k33, k34, k35, k36, XXX, XXX, XXX, k3a, k3b, k3c, k3d, k3e, k3f, k3g, XXX}, \
        {k40, XXX, k42, k43, k44, k45, k46, XXX, k48, XXX, k4a, k4b, k4c, k4d, k4e, k4f, k4g, k4h}, \
        {k50, k51, XXX, k53, XXX, k55, XXX, k57, k58, k59, XXX, k5b, XXX, k5d, XXX, k5f, k5g, k5h}, \
    }
