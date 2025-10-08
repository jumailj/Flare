#include "Font.h"


#include "msdf-atlas-gen.h"
#include "msdfgen.h"

namespace Flare{
    Font::Font(const std::filesystem::path & filepath) 
    {

        msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();

        if (ft) {


            std::string fileString = filepath.string();


            msdfgen::FontHandle* font = msdfgen::loadFont(ft, fileString.c_str());
            if (font) {

                msdfgen::Shape shape;

                if (msdfgen::loadGlyph(shape, font, 'A')) {
                    shape.normalize();
                    //      max.angel

                    msdfgen::edgeColoringSimple(shape, 3.0);
                    
                    
                    msdfgen::Bitmap<float, 3> msdf(32, 32);
                    msdfgen::generateMSDF(msdf, shape, 4.0, 1.0, msdfgen::Vector2(4.0, 4.0f));
                    msdfgen::savePng(msdf, "output.png");

                }


                msdfgen::destroyFont(font);

            }

            msdfgen::deinitializeFreetype(ft);
        }

    }

};

