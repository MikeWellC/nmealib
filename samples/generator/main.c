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
