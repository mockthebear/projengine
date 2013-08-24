#include "objects.h"
#include "maploader.h"

#ifndef _LUAH

#define _LUAH

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}




class luaScript{

    public:
    lua_State *L;
    luaScript();
    ~luaScript();

    char jj[2];
    void loadScript(char *name);
    void registerFunctions(lua_State *L);
    void startEngine();
    void beginEnvoriment();
    protected:

        //Lua binded
        /*! particle */
        static int32_t createParticleEngine(lua_State *L);
        static int32_t setEnabledParticle(lua_State *L);            // setEnabledParticle(part,bool)
        static int32_t setParticleEffectType(lua_State *L);         // setParticleEffectType(part,type)
        static int32_t setParticleMaxSteps(lua_State *L);           // setParticleMaxSteps(part,int)
        static int32_t setEnabledParticleFade(lua_State *L);        // setEnabledParticleFade(part,bool)
        static int32_t setEnabledParticleBlink(lua_State *L);       // setEnabledParticleBlink(part,bool)
        static int32_t particleReset(lua_State *L);                 // particleReset(part)
        static int32_t setParticlePosition(lua_State *L);           // setParticlePosition(part,x,y,bool)
        static int32_t setParticleStorage(lua_State *L);            // setParticleStorage(part,index,var)
        static int32_t setParticleColor(lua_State *L);       // setEnabledParticleColor(part,r,g,b)

        //Standard

        static int32_t setEnableConsole(lua_State *L);
        static int32_t print_console(lua_State *L);
        static int32_t getOS(lua_State *L);


        /*common*/

        static int32_t setCollisionAreaS(lua_State *L);

        static int32_t setObjectPosition(lua_State *L);
        static int32_t getObjectPointerById(lua_State *L);
        static int32_t getObjectIdByPointer(lua_State *L);
        static int32_t createObject_lua(lua_State *L);
        static int32_t setY(lua_State *L);
        static int32_t setType(lua_State *L);
        static int32_t setFont(lua_State *L);
        static int32_t setTY(lua_State *L);
        static int32_t setStack(lua_State *L);
        static int32_t setVy(lua_State *L);
        static int32_t setVx(lua_State *L);
        static int32_t setgY(lua_State *L);
        static int32_t setVisible(lua_State *L);
        static int32_t setX(lua_State *L);
        static int32_t getTicks(lua_State *L);
        static int32_t getY(lua_State *L);
        static int32_t getX(lua_State *L);
        static int32_t getH(lua_State *L);
        static int32_t getAttach(lua_State *L);
        static int32_t setAttach(lua_State *L);
        static int32_t setAttachF(lua_State *L);
        static int32_t createPolygon(lua_State *L);
        static int32_t setPolygonColor(lua_State *L);
        static int32_t delete_(lua_State *L);
        static int32_t flipObject(lua_State *L);
        static int32_t ampliateObject(lua_State *L);
        static int32_t smoothObject(lua_State *L);

        static int32_t setText(lua_State *L);
        static int32_t setAlive(lua_State *L);
        static int32_t setTextColor(lua_State *L);
        static int32_t getObjectStateId(lua_State *L);
        static int32_t getW(lua_State *L);

        static int32_t getMouseX(lua_State *L);
        static int32_t getMouseY(lua_State *L);
        static int32_t deleteObject(lua_State *L);
        static int32_t registerType(lua_State *L);
        static int32_t unregisterType(lua_State *L);
        static int32_t createEffect(lua_State *L);
        static int32_t loadLevel(lua_State *L);
        static int32_t unloadLevel(lua_State *L);
        static int32_t print_log(lua_State *L);
        static int32_t setObjectClips(lua_State *L);
        static int32_t setCollisionArea(lua_State *L);
        static int32_t getCollisionPoint(lua_State *L);
        static int32_t getCollisionPointS(lua_State *L);

        //Sound
        static int32_t loadSound(lua_State *L);
        static int32_t stopMusic(lua_State *L);
        static int32_t pauseMusic(lua_State *L);
        static int32_t resumeMusic(lua_State *L);
        static int32_t playMusic(lua_State *L);
        static int32_t soundFadeOut(lua_State *L);
        static int32_t soundFadeIn(lua_State *L);
        static int32_t setSoundVolume(lua_State *L);
        static int32_t setPositionSound(lua_State *L);

        //Polygon

        static int32_t setPolygonAlpha(lua_State *L);
        static int32_t movePolygonXY(lua_State *L);


        //Effects

        static int32_t setEffectAttachOffsetX(lua_State *L);
        static int32_t setEffectAttachOffsetY(lua_State *L);

};
Objeto *getObjectById(int id_);





extern luaScript *Lua;
extern Objeto *mother;


#endif
