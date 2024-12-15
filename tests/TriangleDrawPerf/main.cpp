#include "SysHelper.h"
#include "BaseLang.hpp"
#include "BaseMath.hpp"
#include "Bitmap.h"

int main()
{
    Bitmap bitmap = BitmapCreate(1920, 1080);

    Vector3 p0 = {     0,     0,  1 };
    Vector3 p1 = {  1919,     0,  1 };
    Vector3 p2 = {  1919,  1079,  1 };

    int drawCount = 100;

    {
        long time1 = SysHelperGetTime();

        for (int i = 0; i < drawCount; i++)
            BitmapDrawTriangleScreenspaceV2(&bitmap, p0, p1, p2, COLOR_GREEN);

        long time2 = SysHelperGetTime();

        cout << "==== " << (time2 - time1) << " ====" << endl;
    }

    return 0;
}
