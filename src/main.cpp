/*#include <math.h>
#include "Methods.h"*/
#include "Globals.h"
#include "Application.h"
/*#include "TestObject.h"
#include "IMovableElement.h"
#include <boost\lexical_cast.hpp>
#include <boost\any.hpp>
#include <iostream>
#include <cassert>*/

int main(int argc, char *argv[])
{
    if(g_config.compare("nope.avi") == 0)
        return -1;
    Application app;
    app.go();
    return 0;
}
