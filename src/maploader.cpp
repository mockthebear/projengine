///         Projeej (Projengine)
///
///         Criado por Matheus Braga Almeida (Mock the bear)
///         Com auxilio de Gabriel Botelho
///         E professor Rodrigo Bonifácio
///
///         Materia Programação orientada a objetos 1/2013
///
///         Não redistribuir sem autorização de Matheus Braga
///

#include "maploader.h"
#include "logs.h"
extern Log *output;
Map::~Map(){
    output->write("deleting stuff\n");

    for (int i=0;i<obj_count;i++){
        delete map_objs[i];
    }
    output->write("pwned\n");
    alive = true;
    if (prev){
        prev->next = next;
    }
    if (next){
        next->prev = prev;
    }
    if (this == last){
        last = prev;

    }
    free(mapBin);
    output->write("ok\n");
    //collision_map->destroy();
    output->write("colmap dead\n");
    delete (collision_map);
    output->write("free\n");
    topSel = NULL;
    output->write("bye\n");
}
Map::Map(char *background,char *mapdir):Objeto(background,-1,-1){
    //vX = 1.5;
    collision_map = new Collision(SCREEN_Width,SCREEN_Height);
    setType(OBJ_MAP);
    FILE *fp = fopen(mapdir,"rb");
    if (fp){
        fseek(fp, 0L, SEEK_END);
        mapSize_bin = ftell(fp);
        mapBin = (unsigned char*)malloc(sizeof(unsigned char)*mapSize_bin+1);
        fseek(fp, 0L, SEEK_SET);
        fread(mapBin, 1, mapSize_bin, fp);
        obj_count = (mapBin[0]*256)+mapBin[1]-1;
        map_objs = (Objeto**)malloc(sizeof(Objeto*)*obj_count);

        int k = 0;
        while (mapBin[k] != 'G'){
            k++;
        }
        //int txtcnt = (mapBin[k+1]*256)+mapBin[k+2]-1;
        k = k+2;
        int i = 3;
        for (int e =0;e<obj_count;e++){
            char nn[35];
            int id = mapBin[i]*256+mapBin[i+1]-1;
            if (id != 1){
                int type = (mapBin[i+2]*256)+mapBin[i+3]-1;
                //i+2 && i+3 == type
                int x_ = (mapBin[i+4]*256)+mapBin[i+5]-1;
                int y_ = (mapBin[i+6]*256)+mapBin[i+7]-1;
                int ox_ = (mapBin[i+8]*256)+mapBin[i+9]-1;
                int oy_ = (mapBin[i+10]*256)+mapBin[i+11]-1;
                int x_p = (mapBin[i+12]*256)+mapBin[i+13]-1;
                int y_p = (mapBin[i+14]*256)+mapBin[i+15]-1;
                if (x_ == y_ && ox_ == oy_ && x_ == oy_){
                    sprintf (nn, "$%d",id);
                    map_objs[e] = (createObject(nn,x_p,y_p));
                    uint8_t coll = map_objs[e]->id;
                    map_objs[e]->state[7] = type;
                    collision_map->setCollisionArea(x_p,y_p,x_p+map_objs[e]->getImage()->w,y_p+map_objs[e]->getImage()->h,coll);
                    //collision_map->reserved[collision_map->Rcount] = map_objs[e];

                }else{
                    sprintf (nn, "a%d;%d;%d;%d;%d",id,x_,y_,ox_,oy_);
                    map_objs[e] = (createObject(nn,x_p,y_p));
                    map_objs[e]->state[7] = type;


                    collision_map->setCollisionArea(x_p,y_p,x_p+ox_,y_p+oy_,map_objs[e]->id);

                }



            }else{
                int R = (mapBin[i+4]*256)+mapBin[i+5]-1;
                int G = (mapBin[i+6]*256)+mapBin[i+7]-1;
                int B = (mapBin[i+8]*256)+mapBin[i+9]-1;

                int x_p = (mapBin[i+12]*256)+mapBin[i+13]-1;
                int y_p = (mapBin[i+14]*256)+mapBin[i+15]-1;

                int txtsize = (mapBin[k+1]*256)+mapBin[k+2]-1;
                char *temp = (char *)malloc(sizeof(char)*txtsize+1);
                int mn;
                k = k+3;
                for (mn=k;mn<k+txtsize;mn++){
                    temp[mn-k] = mapBin[mn];
                }
                temp[txtsize] = '\0';
                k = k+txtsize-1;
                map_objs[e] = (createObject(temp,x_p,y_p));
                map_objs[e]->setTextColor(R,G,B);
                free(temp);

            }
            i = i+17;
        }

    }
    fclose(fp);

}


