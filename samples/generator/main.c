/*
 * This file is part of nmealib.
 *
 * Copyright (c) 2008 Timur Sinitsyn
 * Copyright (c) 2011 Ferry Huberts
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <nmea/nmea.h>

#include <stdio.h>
#include <unistd.h>

int main()
{
    nmeaGENERATOR *gen;
    nmeaINFO info;
    char buff[2048];
    int gen_sz;
    int it;

    nmea_zero_INFO(&info);

    if(0 == (gen = nmea_create_generator(NMEA_GEN_ROTATE, &info)))
        return -1;

    for(it = 0; it < 10000; ++it)
    {
        gen_sz = nmea_generate_from(
            &buff[0], 2048, &info, gen,
            GPGGA | GPGSA | GPGSV | GPRMC | GPVTG
            );

        buff[gen_sz] = 0;
        printf("%s\n", &buff[0]);

        usleep(500000);        
    }

    nmea_gen_destroy(gen);

    return 0;
}
