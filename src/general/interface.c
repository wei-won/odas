
   /**
    * \file     interface.c
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2018-03-18
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <general/interface.h>

    interface_obj * interface_construct() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_undefined;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_blackhole() {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_blackhole;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_file(const char * fileName) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_file;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) malloc(sizeof(char) * (strlen(fileName)+1));
            strcpy(obj->fileName, fileName);

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

    interface_obj * interface_construct_socket(const char * ip, const unsigned int port) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_socket;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) malloc(sizeof(char) * (strlen(ip)+1));
            strcpy(obj->ip, ip);
            obj->port = port;

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;        

    }

   interface_obj * interface_construct_soundcard(const unsigned int card, const unsigned int device) {

       char * deviceName = (char *) malloc(sizeof(char) * 1024);

       sprintf(deviceName, "hw:%u,%u", card, device);

       return interface_construct_soundcard_by_name(deviceName);

   }

   interface_obj * interface_construct_soundcard_by_name(char * deviceName) {

       interface_obj * obj;

       obj = (interface_obj *) malloc(sizeof(interface_obj));

       // +----------------------------------------------------------+
       // | Type                                                     |
       // +----------------------------------------------------------+

       obj->type = interface_soundcard;

       // +----------------------------------------------------------+
       // | Blackhole                                                |
       // +----------------------------------------------------------+

       // (Empty)

       // +----------------------------------------------------------+
       // | File                                                     |
       // +----------------------------------------------------------+

       obj->fileName = (char *) NULL;

       // +----------------------------------------------------------+
       // | Socket                                                   |
       // +----------------------------------------------------------+

       obj->ip = (char *) NULL;
       obj->port = 0;

       // +----------------------------------------------------------+
       // | Soundcard                                                |
       // +----------------------------------------------------------+

       obj->deviceName = deviceName;

       // +----------------------------------------------------------+
       // | Terminal                                                 |
       // +----------------------------------------------------------+

       // (Empty)

       return obj;

   }

    interface_obj * interface_construct_terminal(void) {

        interface_obj * obj;

        obj = (interface_obj *) malloc(sizeof(interface_obj));

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            obj->type = interface_terminal;

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            obj->fileName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+

            obj->ip = (char *) NULL;
            obj->port = 0;

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

        obj->deviceName = (char *) NULL;

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return obj;

    }

   // CHANGES: add interface construction for Apollo
   interface_obj * interface_construct_apollo() {

       interface_obj * obj;

       obj = (interface_obj *) malloc(sizeof(interface_obj));
       obj->type = interface_apollo;
       obj->fileName = (char *) NULL;
       obj->ip = (char *) NULL;
       obj->port = 0;
       obj->deviceName = (char *) NULL;

       return obj;

   }

    interface_obj * interface_clone(const interface_obj * obj) {

        interface_obj * clone;

        clone = interface_construct();

        // +----------------------------------------------------------+
        // | Type                                                     |
        // +----------------------------------------------------------+

            clone->type = obj->type;        

        // +----------------------------------------------------------+
        // | Blackhole                                                |
        // +----------------------------------------------------------+

            // (Empty)

        // +----------------------------------------------------------+
        // | File                                                     |
        // +----------------------------------------------------------+

            if (obj->type == interface_file) {
                
                clone->fileName = (char *) malloc(sizeof(char) * (strlen(obj->fileName) + 1));
                strcpy(clone->fileName, obj->fileName);

            }

        // +----------------------------------------------------------+
        // | Socket                                                   |
        // +----------------------------------------------------------+                

            if (obj->type == interface_socket) {
                
                clone->ip = (char *) malloc(sizeof(char) * (strlen(obj->ip) + 1));
                strcpy(clone->ip, obj->ip);
                clone->port = obj->port;

            }

        // +----------------------------------------------------------+
        // | Soundcard                                                |
        // +----------------------------------------------------------+

            if (obj->type == interface_soundcard) {
                clone->deviceName = obj->deviceName;
            }

        // +----------------------------------------------------------+
        // | Terminal                                                 |
        // +----------------------------------------------------------+

            // (Empty)

        return clone;

    }

    void interface_destroy(interface_obj * obj) {

        if (obj->fileName != NULL) {

            free((void *) obj->fileName);

        }

        /* Will propably be freed somewhere else. Which is a bit ugly.
        if (obj->deviceName != NULL) {

            free((void *) obj->deviceName);

        }
        */

        if (obj->ip != NULL) {

            free((void *) obj->ip);

        }

        free((void *) obj);

    }

    void interface_printf(const interface_obj * obj) {

        if (obj != NULL) {

            switch(obj->type) {

                case interface_blackhole:

                    printf("type = blackhole\n");

                break;

                case interface_file:

                    printf("type = file, fileName = %s\n",obj->fileName);

                break;

                case interface_socket:

                    printf("type = socket, ip = %s, port = %u\n",obj->ip,obj->port);

                break;

                case interface_soundcard:

                    printf("type = soundcard_name, devicename = %s\n",obj->deviceName);

                    break;

                case interface_terminal:

                    printf("type = terminal\n");

                break;

                // CHANGES: add case for Apollo interface
                case interface_apollo:
                    printf("type = apollo\n");
                    break;

            }

        }
        else {

            printf("(null)\n");

        }

    }
