/*
  ==============================================================================

   This file is part of AngelJuice

   which is based on kRAkEn/gORe eJUCE library
   which uses
               Raw Material Software ltd. JUCE library
               AngelCode AngelScript scripting library

   AngelJuice can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   AngelJuice is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA 02111-1307 USA

   @coder	Asnaghi Lucio a.k.a. kRAkEn/gORe

  ==============================================================================
*/

#include "../../libraries/angelscript/angelscript.h"
#include "AngelJuice_AngelScriptCommon.h"
#include "AngelJuice_AngelScriptString.h"
#include "AngelJuice_AngelScriptImaging.h"
#include "../AngelJuice_ScriptableEngine.h"

//==============================================================================
/*
asColours::asColours ()
//  : transparentBlack (Colours::transparentBlack, 0),
//    transparentWhite (Colours::transparentBlack, 0),
//    black (Colours::black, 0),
//    white (Colours::white, 0),
//    blue (Colours::blue, 0),
//    grey (Colours::grey, 0),
//    green (Colours::green, 0),
//    red (Colours::red, 0),
//    yellow (Colours::yellow, 0)
    //==============================================================================
    aliceblue,              antiquewhite,       aqua,               aquamarine,
    azure,                  beige,              bisque,             blanchedalmond,
    blueviolet,             brown,              burlywood,          cadetblue,
    chartreuse,             chocolate,          coral,              cornflowerblue,
    cornsilk,               crimson,            cyan,               darkblue,
    darkcyan,               darkgoldenrod,      darkgrey,           darkgreen,
    darkkhaki,              darkmagenta,        darkolivegreen,     darkorange,
    darkorchid,             darkred,            darksalmon,         darkseagreen,
    darkslateblue,          darkslategrey,      darkturquoise,      darkviolet,
    deeppink,               deepskyblue,        dimgrey,            dodgerblue,
    firebrick,              floralwhite,        forestgreen,        fuchsia,
    gainsboro,              gold,               goldenrod,          greenyellow,
    honeydew,               hotpink,            indianred,          indigo,
    ivory,                  khaki,              lavender,           lavenderblush,
    lemonchiffon,           lightblue,          lightcoral,         lightcyan,
    lightgoldenrodyellow,   lightgreen,         lightgrey,          lightpink,
    lightsalmon,            lightseagreen,      lightskyblue,       lightslategrey,
    lightsteelblue,         lightyellow,        lime,               limegreen,
    linen,                  magenta,            maroon,             mediumaquamarine,
    mediumblue,             mediumorchid,       mediumpurple,       mediumseagreen,
    mediumslateblue,        mediumspringgreen,  mediumturquoise,    mediumvioletred,
    midnightblue,           mintcream,          mistyrose,          navajowhite,
    navy,                   oldlace,            olive,              olivedrab,
    orange,                 orangered,          orchid,             palegoldenrod,
    palegreen,              paleturquoise,      palevioletred,      papayawhip,
    peachpuff,              peru,               pink,               plum,
    powderblue,             purple,             rosybrown,          royalblue,
    saddlebrown,            salmon,             sandybrown,         seagreen,
    seashell,               sienna,             silver,             skyblue,
    slateblue,              slategrey,          snow,               springgreen,
    steelblue,              tan,                teal,               thistle,
    tomato,                 turquoise,          violet,             wheat,
    whitesmoke,             yellowgreen;
{}

static asColour* asColours_findColourForName(const asString& name, const asColour& def)
{
    return new asColour (Colours::findColourForName (name.buffer, def.col));
}

static asColours staticColours;
*/

//==============================================================================
asColour::asColour() : col() {
	refCount = 1;
}
asColour::asColour(int rgba) : col(rgba) {
	refCount = 1;
}
asColour::asColour(int red, int green, int blue, int alpha) :
	col((uint8)red,(uint8)green,(uint8)blue,(uint8)alpha) {
	refCount = 1;
}
asColour::asColour(float red, float green, float blue, float alpha) :
	col((uint8)(red*255),(uint8)(green*255),(uint8)(blue*255),alpha) {
	refCount = 1;
}
asColour::asColour(const Colour &c) : col(c) {
	refCount = 1;
}
asColour::asColour(const Colour &c, int refCount_) : col(c) {
	refCount = refCount_;
}
asColour::asColour(const asColour &c) : col(c.col) {
	refCount = 1;
}
asColour::~asColour() {
	jassert( refCount == 0 );
}

int asColour::addRef() {
	return refCount++;
}
int asColour::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

bool operator==(const asColour &a, const asColour &b) {
	return a.col == b.col;
}
bool operator!=(const asColour &a, const asColour &b) {
	return a.col != b.col;
}

void asColour::getHSB (float* hue,float* saturation,float* brightness){
	col.getHSB(*hue,*saturation,*brightness);
}
asColour* asColour::withAlpha (const uint8 newAlpha){
	return new asColour(col.withAlpha(newAlpha));
}
asColour* asColour::withAlpha (const float newAlpha){
	return new asColour(col.withAlpha(newAlpha));
}
asColour* asColour::withMultipliedAlpha (const float alphaMultiplier){
	return new asColour(col.withMultipliedAlpha(alphaMultiplier));
}
asColour* asColour::overlaidWith (const asColour& foregroundColour){
	return new asColour(col.overlaidWith(foregroundColour.col));
}
asColour* asColour::withHue (const float newHue){
	return new asColour(col.withHue(newHue));
}
asColour* asColour::withSaturation (const float newSaturation){
	return new asColour(col.withSaturation(newSaturation));
}
asColour* asColour::withBrightness (const float newBrightness){
	return new asColour(col.withBrightness(newBrightness));
}
asColour* asColour::withRotatedHue (const float amountToRotate){
	return new asColour(col.withRotatedHue(amountToRotate));
}
asColour* asColour::withMultipliedSaturation (const float multiplier){
	return new asColour(col.withMultipliedSaturation(multiplier));
}
asColour* asColour::withMultipliedBrightness (const float amount){
	return new asColour(col.withMultipliedBrightness(amount));
}
asColour* asColour::brighter (float amountBrighter){
	return new asColour(col.brighter(amountBrighter));
}
asColour* asColour::darker (float amountDarker){
	return new asColour(col.darker(amountDarker));
}
asColour* asColour::contrasting (const float amount){
	return new asColour(col.contrasting(amount));
}

static void ConstructColour(asColour *thisPointer) {
	new(thisPointer) asColour();
}
static void ConstructColourByColour(const asColour& other, asColour *thisPointer) {
    new(thisPointer) asColour(other);
}
static void ConstructColour1i(int rgba, asColour *thisPointer) {
	new(thisPointer) asColour(rgba);
}
static void ConstructColour3i(int r, int g, int b, asColour *thisPointer) {
	new(thisPointer) asColour(r,g,b,255);
}
static void ConstructColour4i(int r, int g, int b, int a, asColour *thisPointer) {
    new(thisPointer) asColour(r,g,b,a);
}
static void ConstructColour3f(float r, float g, float b, asColour *thisPointer) {
	new(thisPointer) asColour(r,g,b,1.0f);
}
static void ConstructColour4f(float r, float g, float b, float a, asColour *thisPointer) {
    new(thisPointer) asColour(r,g,b,a);
}

void asColour::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Colour", sizeof(asColour), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f()",                        asFUNCTION(ConstructColour), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(int)",                     asFUNCTION(ConstructColour1i), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(int,int,int)",             asFUNCTION(ConstructColour3i), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(int,int,int,int)",         asFUNCTION(ConstructColour4i), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(float,float,float)",       asFUNCTION(ConstructColour3f), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(float,float,float,float)", asFUNCTION(ConstructColour4f), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_CONSTRUCT,  "void f(const Colour& in)",        asFUNCTION(ConstructColourByColour), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_ADDREF,     "void f()",                        asMETHOD(asColour,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Colour", asBEHAVE_RELEASE,    "void f()",                        asMETHOD(asColour,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,      "bool f(const Colour &in, const Colour &in)",asFUNCTIONPR(operator==, (const asColour &, const asColour &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,   "bool f(const Colour &in, const Colour &in)",asFUNCTIONPR(operator!=, (const asColour &, const asColour &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "uint getARGB()",                             asMETHOD(Colour,getARGB), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "uint8 getRed()",                             asMETHOD(Colour,getRed), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "uint8 getGreen()",                           asMETHOD(Colour,getGreen), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "uint8 getBlue()",                            asMETHOD(Colour,getBlue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "uint8 getAlpha()",                           asMETHOD(Colour,getAlpha), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getFloatRed()",                        asMETHOD(Colour,getFloatRed), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getFloatGreen()",                      asMETHOD(Colour,getFloatGreen), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getFloatBlue()",                       asMETHOD(Colour,getFloatBlue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getFloatAlpha()",                      asMETHOD(Colour,getFloatAlpha), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getHue()",                             asMETHOD(Colour,getHue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getSaturation()",                      asMETHOD(Colour,getSaturation), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "float getBrightness()",                      asMETHOD(Colour,getBrightness), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "bool isOpaque()",                            asMETHOD(Colour,isOpaque), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "bool isTransparent()",                       asMETHOD(Colour,isTransparent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "void getHSB(float&out,float&out,float&out)", asMETHOD(asColour,getHSB), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withAlpha(uint8)",                   asMETHODPR(asColour,withAlpha,(const uint8),asColour*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withAlpha(float)",                   asMETHODPR(asColour,withAlpha,(const float),asColour*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withMultipliedAlpha(float)",         asMETHOD(asColour,withMultipliedAlpha), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ overlaidWith(const Colour& in)",     asMETHOD(asColour,overlaidWith), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withHue(float)",                     asMETHOD(asColour,withHue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withSaturation(float)",              asMETHOD(asColour,withSaturation), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withBrightness(float)",              asMETHOD(asColour,withBrightness), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withRotatedHue(float)",              asMETHOD(asColour,withRotatedHue), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withMultipliedSaturation(float)",    asMETHOD(asColour,withMultipliedSaturation), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ withMultipliedBrightness(float)",    asMETHOD(asColour,withMultipliedBrightness), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ brighter(float)",                    asMETHOD(asColour,brighter), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ darker(float)",                      asMETHOD(asColour,darker), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Colour", "Colour@ contrasting(float)",                 asMETHOD(asColour,contrasting), asCALL_THISCALL); jassert( r >= 0 );

    // colours
//    r = engine->RegisterObjectType("Colours__", sizeof(asColours), asOBJ_CLASS); jassert( r >= 0 );
//    r = engine->RegisterObjectBehaviour("Colours__", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
//    r = engine->RegisterObjectBehaviour("Colours__", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
//    r = engine->RegisterObjectMethod("Colours__", "Colour@ findColourForName(const String& in, const Colour& in)", asFUNCTION(asColours_findColourForName), asCALL_CDECL); jassert( r >= 0 );
//    r = engine->RegisterObjectProperty("Colours__", "Colour black",    offsetof(asColours, black));  jassert( r >= 0 );
//    r = engine->RegisterGlobalProperty("Colours__ Colours", (void*)&staticColours);  jassert( r >= 0 );
}


//==============================================================================
asImage::asImage(int imageWidth, int imageHeight) {
	image = new Image(Image::ARGB,imageWidth,imageHeight,true);
	refCount = 1;
}
asImage::asImage(const Image &i) {
	image = new Image(i);
	refCount = 1;
}
asImage::asImage(Image* i) {
	image = new Image(*i);
	refCount = 1;
}
asImage::asImage(const asImage &i) {
	image = new Image(*(i.image));
	refCount = 1;
}
asImage::asImage(asImage* i) {
	image = new Image(*(i->image));
	refCount = 1;
}
asImage::~asImage() {
	jassert( refCount == 0 );
	if (image)
		delete image;
}

int asImage::addRef() {
	return refCount++;
}
int asImage::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

int asImage::getWidth() {
	return image->getWidth();
}
int asImage::getHeight(){
	return image->getWidth();
}
bool asImage::isARGB() {
    return image->isARGB();
}
bool asImage::isRGB(){
    return image->isRGB();
}
bool asImage::hasAlphaChannel(){
    return image->hasAlphaChannel();
}
void asImage::clear (int x, int y, int w, int h, const asColour& colourToClearTo){
	image->clear(x,y,w,h,colourToClearTo.col);
}
asImage* asImage::createCopy (int newWidth, int newHeight){
	return new asImage(*image->createCopy(newWidth,newHeight));
}
asColour* asImage::getPixelAt (const int x, const int y){
	return new asColour(image->getPixelAt(x,y));
}
void asImage::setPixelAt (const int x, const int y, const asColour& colour){
	image->setPixelAt(x,y,colour.col);
}
void asImage::multiplyAlphaAt (const int x, const int y, const float multiplier){
	image->multiplyAlphaAt(x,y,multiplier);
}
void asImage::multiplyAllAlphas (const float amountToMultiplyBy){
	image->multiplyAllAlphas(amountToMultiplyBy);
}
void asImage::desaturate (){
    image->desaturate();
}
void asImage::moveImageSection (int destX, int destY, int sourceX, int sourceY, int width, int height){
	image->moveImageSection(destX,destY,sourceX,sourceY,width,height);
}

asIScriptArray* asImage::lockPixelDataReadWrite (int x, int y, int w, int h, int* lineStride, int* pixelStride)
// uint8* asImage::lockPixelDataReadWrite (int x, int y, int w, int h, int* lineStride, int* pixelStride)
{
	uint8* pixels = image->lockPixelDataReadWrite (x,y,w,h,*lineStride,*pixelStride);
	int numPixels = (w * h) - (w * y) - (x);

	asIScriptEngine* engine = ScriptableEngine::getInstance()->getEngine();
	int arrayTypeId = engine->GetTypeIdByDecl(0, "uint8[]");
	asIScriptArray *arrayObject = (asIScriptArray*) engine->CreateScriptObject (arrayTypeId);

	arrayObject->Resize (numPixels);

	for (int i = 0; i < numPixels; i++)
	{
		*((uint8*)arrayObject->GetElementPointer(i)) = pixels[i];
	}

	return arrayObject;
}

void asImage::releasePixelDataReadWrite () {
    image->releasePixelDataReadWrite (0);
}

asImage* loadImageFromFile(const asString& fileName)
{
    try
    {
        File fileToLoad(fileName.buffer);
        if (fileToLoad.existsAsFile())
        {
            Image* loadedImage = ImageFileFormat::loadFrom (fileToLoad);
            asImage* imageToReturn = new asImage(loadedImage);
            delete loadedImage;
            return imageToReturn;
        }
        else
        {
            asIScriptContext *context = asGetActiveContext();
            String errorString = T("Cannot find ");
            errorString << fileToLoad.getFullPathName();
            context->SetException ((const char*)errorString);
            return 0;
        }
    }
    catch (...)
    {
        asIScriptContext *context = asGetActiveContext();
        context->SetException ("Something bad happened when loading image!");
        return 0;
    }
}

void saveImageToFile(const asImage& imgToSave, const asString& fileName)
{
    try
    {
        File fileToSave(fileName.buffer);
        if (fileToSave.existsAsFile() && fileToSave.hasWriteAccess ())
            fileToSave.deleteFile();

        OutputStream* out = fileToSave.createOutputStream();

        if (out == 0)
        {
            asIScriptContext *context = asGetActiveContext();
            context->SetException ("You don't have permission to write that file!");
            return;
        }

        if (fileToSave.getFileExtension().toLowerCase()==T(".jpg") ||
            fileToSave.getFileExtension().toLowerCase()==T(".jpeg"))
        {
            JPEGImageFormat jpegFormat;
            jpegFormat.writeImageToStream(*(imgToSave.image),*out);
            delete out;
        }
        else
        if (fileToSave.getFileExtension().toLowerCase()==T(".png"))
        {
            PNGImageFormat pngFormat;
            pngFormat.writeImageToStream(*(imgToSave.image),*out);
            delete out;
        }
        else
        {
            delete out;
            asIScriptContext *context = asGetActiveContext();
            context->SetException ("This ImageFormat isn't supported!");
        }
    }
    catch (...)
    {
        asIScriptContext *context = asGetActiveContext();
        context->SetException ("Something bad happened when saving image!");
    }
}

static void ConstructImage(int width, int height, asImage *thisPointer) {
	new(thisPointer) asImage(width,height);
}
static void ConstructImageByImage(const asImage& other, asImage *thisPointer) {
    new(thisPointer) asImage(other);
}

void asImage::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Image", sizeof(asImage), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Image", asBEHAVE_CONSTRUCT,  "void f(int,int)",                    asFUNCTION(ConstructImage), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Image", asBEHAVE_CONSTRUCT,  "void f(const Image& in)",            asFUNCTION(ConstructImageByImage), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Image", asBEHAVE_ADDREF,     "void f()",                           asMETHOD(asImage,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Image", asBEHAVE_RELEASE,    "void f()",                           asMETHOD(asImage,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "int getWidth()",                                             asMETHOD(asImage,getWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "int getHeight()",                                            asMETHOD(asImage,getHeight), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "bool isARGB()",                                              asMETHOD(asImage,isARGB), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "bool isRGB()",                                               asMETHOD(asImage,isRGB), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "bool hasAlphaChannel()",                                     asMETHOD(asImage,hasAlphaChannel), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "void clear(int,int,int,int,const Colour& in)",               asMETHOD(asImage,clear), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "Image@ createCopy(int,int)",                                 asMETHOD(asImage,createCopy), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "Colour@ getPixelAt(int,int)",                                asMETHOD(asImage,getPixelAt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "void setPixelAt(int,int,const Colour& in)",                  asMETHOD(asImage,setPixelAt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "void multiplyAlphaAt(int,int,float)",                        asMETHOD(asImage,multiplyAlphaAt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Image", "void multiplyAllAlphas(float)",                              asMETHOD(asImage,multiplyAllAlphas), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "void desaturate()",                                          asMETHOD(asImage,desaturate), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Image", "void moveImageSection(int,int,int,int,int,int)",             asMETHOD(asImage,moveImageSection), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Image", "uint8[]@ lockPixelDataReadWrite(int,int,int,int,int&,int&)", asMETHOD(asImage,lockPixelDataReadWrite), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Image", "void releasePixelDataReadWrite()",                           asMETHOD(asImage,releasePixelDataReadWrite), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterGlobalFunction("Image@ loadImage(const String& in)",                         asFUNCTION(loadImageFromFile), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalFunction("void saveImage(const Image& in, const String& in)",          asFUNCTION(saveImageToFile), asCALL_CDECL); jassert( r >= 0 );
}


//==============================================================================
asImageConvolutionKernel::asImageConvolutionKernel(const int size)
    : kernel (size), refCount (1)
{}

asImageConvolutionKernel::~asImageConvolutionKernel() {
    jassert (refCount == 0);
}

int asImageConvolutionKernel::addRef() {
    return refCount++;
}
int asImageConvolutionKernel::release() {
    if( --refCount == 0 ) {
        delete this;
        return 0;
    }
    return refCount;
}

void asImageConvolutionKernel::applyToImage (asImage* destImage,
                                             asImage* sourceImage,
                                             int x,
                                             int y,
                                             int width,
                                             int height)
{
    kernel.applyToImage (*(destImage->image), sourceImage->image, x, y, width, height);
}

static void ConstructImageConvolutionKernel(int size, asImageConvolutionKernel *thisPointer) {
    new(thisPointer) asImageConvolutionKernel(size);
}

void asImageConvolutionKernel::registerObjectType(asIScriptEngine *engine)
{
    int r;
    r = engine->RegisterObjectType("ImageConvolutionKernel", sizeof(asImageConvolutionKernel), asOBJ_CLASS_CD); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("ImageConvolutionKernel", asBEHAVE_CONSTRUCT,  "void f(int)",                 asFUNCTION(ConstructImageConvolutionKernel), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("ImageConvolutionKernel", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asImageConvolutionKernel,addRef), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("ImageConvolutionKernel", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asImageConvolutionKernel,release), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void clear()",                                        asMETHOD(ImageConvolutionKernel,clear), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void setKernelValue(int,int,float)",                  asMETHOD(ImageConvolutionKernel,setKernelValue), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void setOverallSum(float)",                           asMETHOD(ImageConvolutionKernel,setOverallSum), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void rescaleAllValues(float)",                        asMETHOD(ImageConvolutionKernel,rescaleAllValues), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void createGaussianBlur(float)",                      asMETHOD(ImageConvolutionKernel,createGaussianBlur), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "int getKernelSize() const",                           asMETHOD(ImageConvolutionKernel,getKernelSize), asCALL_THISCALL); jassert( r >= 0 );
//    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "float** getValues() const",                         asMETHOD(ImageConvolutionKernel,getValues), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("ImageConvolutionKernel", "void applyToImage(Image@+,Image@+,int,int,int,int)",  asMETHOD(asImageConvolutionKernel,applyToImage), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asFont::asFont() :
	font(), refCount(1) {
}
asFont::asFont(const float fontHeight, const int styleFlags) :
	font(fontHeight,styleFlags), refCount(1) {
}
asFont::asFont(const Font &f) :
	font(f), refCount(1) {
}
asFont::asFont(const asFont &f) :
	font(f.font), refCount(1) {
}
asFont::~asFont() {
	jassert( refCount == 0 );
}

int asFont::addRef() {
	return refCount++;
}
int asFont::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

const asFont& asFont::operator= (const asFont& other) {
	font = other.font;
	return *this;
}
bool operator== (const asFont& a, const asFont& b) { return a.font == b.font; }
bool operator!= (const asFont& a, const asFont& b) { return a.font != b.font; }

asString* asFont::getTypefaceName() {
	return new asString(font.getTypefaceName());
}

static void ConstructFont(asFont *thisPointer) {
	new(thisPointer) asFont();
}
static void ConstructFontByHeight(float fontHeight, int styleFlags, asFont *thisPointer) {
	new(thisPointer) asFont(fontHeight,styleFlags);
}
static void ConstructFontByFont(const asFont& other, asFont *thisPointer) {
	new(thisPointer) asFont(other);
}

void asFont::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Font", sizeof(asFont), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_CONSTRUCT,  "void f()",                       asFUNCTION(ConstructFont), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_CONSTRUCT,  "void f(float,int)",              asFUNCTION(ConstructFontByHeight), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_CONSTRUCT,  "void f(const Font& in)",         asFUNCTION(ConstructFontByFont), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_ADDREF,     "void f()",                       asMETHOD(asFont,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_RELEASE,    "void f()",                       asMETHOD(asFont,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Font", asBEHAVE_ASSIGNMENT, "Font &f(const Font &in)",        asMETHODPR(asFont, operator=, (const asFont&), asFont&), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,      "bool f(const Font &in, const Font &in)", asFUNCTIONPR(operator==, (const asFont &, const asFont &), bool), asCALL_CDECL); jassert( r >= 0 );
    r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,   "bool f(const Font &in, const Font &in)", asFUNCTIONPR(operator!=, (const asFont &, const asFont &), bool), asCALL_CDECL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Font", "String@ getTypefaceName()",                              asMETHOD(asFont,getTypefaceName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setTypefaceName(const String& in)",                 asMETHOD(Font,setTypefaceName), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getHeight()",                                      asMETHOD(Font,getHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setHeight(float)",                                  asMETHOD(Font,setHeight), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setHeightWithoutChangingWidth(float)",              asMETHOD(Font,setHeightWithoutChangingWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getAscent()",                                      asMETHOD(Font,getAscent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getDescent()",                                     asMETHOD(Font,getDescent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "int getStyleFlags()",                                    asMETHOD(Font,getStyleFlags), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Font", "void setStyleFlags(int)",                                asMETHOD(Font,setStyleFlags), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setBold(bool)",                                     asMETHOD(Font,setBold), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setItalic(bool)",                                   asMETHOD(Font,setItalic), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setUnderline(bool)",                                asMETHOD(Font,setUnderline), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "bool isBold()",                                          asMETHOD(Font,isBold), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "bool isItalic()",                                        asMETHOD(Font,isItalic), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "bool isUnderlined()",                                    asMETHOD(Font,isUnderlined), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setHorizontalScale(float)",                         asMETHOD(Font,setHorizontalScale), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getHorizontalScale()",                             asMETHOD(Font,getHorizontalScale), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setExtraKerningFactor(float)",                      asMETHOD(Font,setExtraKerningFactor), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getExtraKerningFactor()",                          asMETHOD(Font,getExtraKerningFactor), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void setSizeAndStyle(float,int,float,float)",            asMETHOD(Font,setSizeAndStyle), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "void resetToDefaultState()",                             asMETHOD(Font,resetToDefaultState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "int getStringWidth(const String& in)",                   asMETHOD(Font,getStringWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Font", "float getStringWidthFloat(const String& in)",            asMETHOD(Font,getStringWidthFloat), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asAffineTransform::asAffineTransform() {
	transform = AffineTransform::identity;
	refCount = 1;
}
asAffineTransform::asAffineTransform(const AffineTransform &at) {
	transform = at;
	refCount = 1;
}
asAffineTransform::asAffineTransform(const asAffineTransform &at) {
	transform = at.transform;
	refCount = 1;
}
asAffineTransform::~asAffineTransform() {
	jassert( refCount == 0 );
}

int asAffineTransform::addRef() {
	return refCount++;
}
int asAffineTransform::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asAffineTransform& asAffineTransform::operator=(const asAffineTransform &other) {
	transform = other.transform;
	return *this;
}

void asAffineTransform::transformPoint (float* x, float* y) {
	transform.transformPoint(*x,*y);
}
asAffineTransform& asAffineTransform::translated (float deltaX, float deltaY) {
	transform = transform.translated(deltaX,deltaY);
	return *this;
}
asAffineTransform& asAffineTransform::rotated (float angleInRadians) {
	transform = transform.rotated(angleInRadians);
	return *this;
}
asAffineTransform& asAffineTransform::rotated (float angleInRadians, float pivotX, float pivotY) {
	transform = transform.rotated(angleInRadians,pivotX,pivotY);
	return *this;
}
asAffineTransform& asAffineTransform::scaled (float factorX, float factorY) {
	transform = transform.scaled(factorX,factorY);
	return *this;
}
asAffineTransform& asAffineTransform::sheared (float shearX, float shearY) {
	transform = transform.sheared(shearX,shearY);
	return *this;
}
asAffineTransform& asAffineTransform::inverted() {
	transform = transform.inverted();
	return *this;
}
asAffineTransform& asAffineTransform::followedBy (const asAffineTransform& other) {
	transform = transform.followedBy(other.transform);
	return *this;
}

static void ConstructAffineTransform(asAffineTransform *thisPointer) {
	new(thisPointer) asAffineTransform();
}
static void ConstructAffineTransformByAffineTransform(const asAffineTransform& other, asAffineTransform *thisPointer) {
    new(thisPointer) asAffineTransform(other);
}

void asAffineTransform::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("AffineTransform", sizeof(asAffineTransform), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("AffineTransform", asBEHAVE_CONSTRUCT,  "void f()",                           asFUNCTION(ConstructAffineTransform), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("AffineTransform", asBEHAVE_CONSTRUCT,  "void f(const AffineTransform& in)",  asFUNCTION(ConstructAffineTransformByAffineTransform), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("AffineTransform", asBEHAVE_ADDREF,     "void f()",                           asMETHOD(asAffineTransform,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("AffineTransform", asBEHAVE_RELEASE,    "void f()",                           asMETHOD(asAffineTransform,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("AffineTransform", asBEHAVE_ASSIGNMENT, "AffineTransform &f(const AffineTransform &in)",     asMETHODPR(asAffineTransform, operator=, (const asAffineTransform&), asAffineTransform&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "void transformPoint(int& out,int& out)",                     asMETHOD(asAffineTransform,transformPoint), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& translated(float,float)",                   asMETHOD(asAffineTransform,translated), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& rotated(float)",                            asMETHODPR(asAffineTransform,rotated,(float),asAffineTransform&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& rotated(float,float,float)",                asMETHODPR(asAffineTransform,rotated,(float,float,float),asAffineTransform&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& scaled(float,float)",                       asMETHOD(asAffineTransform,scaled), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& sheared(float,float)",                      asMETHOD(asAffineTransform,sheared), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& inverted()",                                asMETHOD(asAffineTransform,inverted), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "AffineTransform& followedBy(const AffineTransform& in)",     asMETHOD(asAffineTransform,followedBy), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "bool isIdentity()",                                          asMETHOD(AffineTransform,isIdentity), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("AffineTransform", "bool isSingularity()",                                       asMETHOD(AffineTransform,isSingularity), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asPoint::asPoint() :
	refCount(1) {
}
asPoint::asPoint(float x, float y) :
	point(x,y), refCount(1) {
}
asPoint::asPoint(const Point &p) :
	point(p), refCount(1) {
}
asPoint::asPoint(const asPoint &p) :
	point(p.point), refCount(1) {
}
asPoint::~asPoint() {
	jassert( refCount == 0 );
}

int asPoint::addRef() {
	return refCount++;
}
int asPoint::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asPoint& asPoint::operator=(const asPoint &other) {
	point = other.point;
	return *this;
}

static void ConstructPoint(asPoint *thisPointer) {
	new(thisPointer) asPoint();
}
static void ConstructPointByCoords(float x, float y, asPoint *thisPointer) {
	new(thisPointer) asPoint(x,y);
}
static void ConstructPointByPoint(const asPoint& other, asPoint *thisPointer) {
    new(thisPointer) asPoint(other);
}

void asPoint::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Point", sizeof(asPoint), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_CONSTRUCT,  "void f()",                           asFUNCTION(ConstructPoint), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_CONSTRUCT,  "void f(float,float)",                asFUNCTION(ConstructPointByCoords), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_CONSTRUCT,  "void f(const Point& in)",            asFUNCTION(ConstructPointByPoint), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_ADDREF,     "void f()",                           asMETHOD(asPoint,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_RELEASE,    "void f()",                           asMETHOD(asPoint,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Point", asBEHAVE_ASSIGNMENT, "Point &f(const Point &in)",          asMETHODPR(asPoint, operator=, (const asPoint&), asPoint&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Point", "float getX()",                                               asMETHOD(Point,getX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Point", "float getY()",                                               asMETHOD(Point,getY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Point", "void setXY(float,float)",                                    asMETHOD(Point,setXY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Point", "void applyTransform(const AffineTransform& in)",             asMETHOD(Point,applyTransform), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asLine::asLine() :
	refCount(1) {
}
asLine::asLine(float sx,float sy,float ex,float ey) :
	line(sx,sy,ex,ey), refCount(1) {
}
asLine::asLine(const Line &l) :
	line(l), refCount(1) {
}
asLine::asLine(const asLine &l) :
	line(l.line), refCount(1) {
}
asLine::asLine(const asPoint &s,const asPoint &e) :
	line(s.point,e.point), refCount(1) {
}
asLine::~asLine() {
	jassert( refCount == 0 );
}

int asLine::addRef() {
	return refCount++;
}
int asLine::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asLine& asLine::operator=(const asLine &other) {
	line = other.line;
	return *this;
}

bool operator== (const asLine& a, const asLine& b) { return a.line == b.line; }
bool operator!= (const asLine& a, const asLine& b) { return a.line != b.line; }

asPoint* asLine::getStart(){
	return new asPoint(line.getStart());
}
asPoint* asLine::getEnd(){
	return new asPoint(line.getEnd());
}
asPoint* asLine::getPointAlongLine (float distanceFromStart){
	return new asPoint(line.getPointAlongLine(distanceFromStart));
}
asPoint* asLine::getPointAlongLine (float distanceFromStart, float perpendicularDistance){
	return new asPoint(line.getPointAlongLine(distanceFromStart,perpendicularDistance));
}
asPoint* asLine::getPointAlongLineProportionally (float proportionOfLength){
	return new asPoint(line.getPointAlongLineProportionally(proportionOfLength));
}
asLine* asLine::withShortenedStart (float distanceToShortenBy){
	return new asLine(line.withShortenedStart(distanceToShortenBy));
}
asLine* asLine::withShortenedEnd (float distanceToShortenBy){
	return new asLine(line.withShortenedEnd(distanceToShortenBy));
}
bool asLine::intersects(const asLine& other, float* x, float* y) {
	return line.intersects(other.line,*x,*y);
}

static void ConstructLine(asLine *thisPointer) {
	new(thisPointer) asLine();
}
static void ConstructLineByCoords(float sx, float sy, float ex, float ey, asLine *thisPointer) {
	new(thisPointer) asLine(sx,sy,ex,ey);
}
static void ConstructLineByLine(const asLine& other, asLine *thisPointer) {
	new(thisPointer) asLine(other);
}
static void ConstructLineByPoints(const asPoint& x, const asPoint& y, asLine *thisPointer) {
    new(thisPointer) asLine(x,y);
}

void asLine::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Line", sizeof(asPoint), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_CONSTRUCT,  "void f()",                                 asFUNCTION(ConstructLine), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_CONSTRUCT,  "void f(float,float,float,float)",          asFUNCTION(ConstructLineByCoords), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_CONSTRUCT,  "void f(const Line& in)",                   asFUNCTION(ConstructLineByLine), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_CONSTRUCT,  "void f(const Point& in,const Point& in)",  asFUNCTION(ConstructLineByPoints), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_ADDREF,     "void f()",                                 asMETHOD(asLine,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_RELEASE,    "void f()",                                 asMETHOD(asLine,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Line", asBEHAVE_ASSIGNMENT, "Line &f(const Line &in)",                  asMETHODPR(asLine, operator=, (const asLine&), asLine&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,      "bool f(const Line &in, const Line &in)",           asFUNCTIONPR(operator==, (const asLine &, const asLine &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,   "bool f(const Line &in, const Line &in)",           asFUNCTIONPR(operator!=, (const asLine &, const asLine &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getStartX()",                                                asMETHOD(Line,getStartX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getStartY()",                                                asMETHOD(Line,getStartY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getEndX()",                                                  asMETHOD(Line,getEndX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getEndY()",                                                  asMETHOD(Line,getEndY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "void setStart(float,float)",                                       asMETHODPR(Line,setStart,(const float,const float),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "void setEnd(float,float)",                                         asMETHODPR(Line,setEnd,(const float,const float),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "void setStart(const Point& in)",                                   asMETHODPR(Line,setStart,(const Point&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "void setEnd(const Point& in)",                                     asMETHODPR(Line,setEnd,(const Point&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "void applyTransform(const AffineTransform& in)",                   asMETHOD(Line,applyTransform), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getLength()",                                                asMETHOD(Line,getLength), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "bool isVertical()",                                                asMETHOD(Line,isVertical), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "bool isHorizontal()",                                              asMETHOD(Line,isHorizontal), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "float getAngle()",                                                 asMETHOD(Line,getAngle), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "bool intersects(const Line& in, float& out, float& out)",          asMETHOD(asLine,intersects), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "Point@ getPointAlongLine(float)",                                  asMETHODPR(asLine,getPointAlongLine,(float),asPoint*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "Point@ getPointAlongLine(float,float)",                            asMETHODPR(asLine,getPointAlongLine,(float,float),asPoint*), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "Point@ getPointAlongLineProportionally(float)",                    asMETHOD(asLine,getPointAlongLineProportionally), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Line", "float getDistanceFromLine(float,float)",                           asMETHOD(Line,getDistanceFromLine), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Line", "float findNearestPointTo(float,float)",                            asMETHOD(Line,findNearestPointTo), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Line", "bool isPointAbove(float,float)",                                   asMETHOD(Line,isPointAbove), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Line", "Line@ withShortenedStart(float)",                                  asMETHOD(asLine,withShortenedStart), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Line", "Line@ withShortenedEnd(float)",                                    asMETHOD(asLine,withShortenedEnd), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Line", "bool clipToPath(const Path& in, bool)",                            asMETHOD(Line,clipToPath), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asRectangle::asRectangle() :
	refCount(1) {
}
asRectangle::asRectangle(int x, int y, int w, int h) :
	rect(x,y,w,h), refCount(1) {
}
asRectangle::asRectangle(const Rectangle &r) :
	rect(r), refCount(1) {
}
asRectangle::asRectangle(const asRectangle &r) :
	rect(r.rect), refCount(1) {
}
asRectangle::~asRectangle() {
	jassert( refCount == 0 );
}

int asRectangle::addRef() {
	return refCount++;
}
int asRectangle::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asRectangle& asRectangle::operator=(const asRectangle &other) {
	rect = other.rect;
	return *this;
}

bool operator== (const asRectangle& a, const asRectangle& b) { return a.rect == b.rect; }
bool operator!= (const asRectangle& a, const asRectangle& b) { return a.rect != b.rect; }

asRectangle* asRectangle::translated (int x, int y) {
    return new asRectangle (rect.translated (x, y));
}

asRectangle* asRectangle::expanded (int x, int y) {
    return new asRectangle (rect.translated (x, y));
}

asRectangle* asRectangle::getIntersection (const asRectangle& other) {
    return new asRectangle (rect.getIntersection (other.rect));
}

asRectangle* asRectangle::getUnion (const asRectangle& other) {
    return new asRectangle (rect.getUnion (other.rect));
}

bool asRectangle::intersectRectangle (int* x, int* y, int* w, int* h) {
    return rect.intersectRectangle (*x, *y, *w, *h);
}

static void ConstructRectangle(asRectangle *thisPointer) {
	new(thisPointer) asRectangle();
}
static void ConstructRectangleByCoords(int x, int y, int w, int h, asRectangle *thisPointer) {
	new(thisPointer) asRectangle(x,y,w,h);
}
static void ConstructRectangleByRectangle(const asRectangle& other, asRectangle *thisPointer) {
    new(thisPointer) asRectangle(other);
}

void asRectangle::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Rectangle", sizeof(asRectangle), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_CONSTRUCT,  "void f()",                            asFUNCTION(ConstructRectangle), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_CONSTRUCT,  "void f(int,int,int,int)",             asFUNCTION(ConstructRectangleByCoords), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_CONSTRUCT,  "void f(const Rectangle& in)",         asFUNCTION(ConstructRectangleByRectangle), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_ADDREF,     "void f()",                            asMETHOD(asRectangle,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_RELEASE,    "void f()",                            asMETHOD(asRectangle,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Rectangle", asBEHAVE_ASSIGNMENT, "Rectangle &f(const Rectangle &in)",   asMETHODPR(asRectangle, operator=, (const asRectangle&), asRectangle&), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,      "bool f(const Rectangle &in, const Rectangle &in)", asFUNCTIONPR(operator==, (const asRectangle &, const asRectangle &), bool), asCALL_CDECL); jassert( r >= 0 );
	r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,   "bool f(const Rectangle &in, const Rectangle &in)", asFUNCTIONPR(operator!=, (const asRectangle &, const asRectangle &), bool), asCALL_CDECL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Rectangle", "int getX()",                                                  asMETHOD(Rectangle,getX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "int getY()",                                                  asMETHOD(Rectangle,getY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "int getWidth()",                                              asMETHOD(Rectangle,getWidth), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "int getHeight()",                                             asMETHOD(Rectangle,getHeight), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "int getRight()",                                              asMETHOD(Rectangle,getRight), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "int getBottom()",                                             asMETHOD(Rectangle,getBottom), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "int getCentreX()",                                            asMETHOD(Rectangle,getCentreX), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "int getCentreY()",                                            asMETHOD(Rectangle,getCentreY), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "bool isEmpty()",                                              asMETHOD(Rectangle,isEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "void setPosition(int,int)",                                   asMETHOD(Rectangle,setPosition), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "void setSize(int,int)",                                       asMETHOD(Rectangle,setSize), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "void setBounds(int,int,int,int)",                             asMETHOD(Rectangle,setBounds), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "void translate(int,int)",                                     asMETHOD(Rectangle,translate), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "Rectangle@ translated(int,int)",                              asMETHOD(asRectangle,translated), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "void expand(int,int)",                                        asMETHOD(Rectangle,expand), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "Rectangle@ expanded(int,int)",                                asMETHOD(asRectangle,expanded), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "bool contains(int,int)",                                      asMETHODPR(Rectangle,contains,(const int, const int) const, bool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "bool contains(const Rectangle &in)",                          asMETHODPR(Rectangle,contains,(const Rectangle&) const, bool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "bool intersects(const Rectangle &in)",                        asMETHOD(Rectangle,intersects), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "Rectangle@ getIntersection(const Rectangle &in)",             asMETHOD(asRectangle,getIntersection), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "bool intersectRectangle(int& out,int& out,int& out,int& out)",asMETHOD(asRectangle,intersectRectangle), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "Rectangle@ getUnion(const Rectangle &in)",                    asMETHOD(asRectangle,getUnion), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Rectangle", "bool enlargeIfAdjacent(const Rectangle &in)",                 asMETHOD(Rectangle,enlargeIfAdjacent), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Rectangle", "bool reduceIfPartlyContainedIn(const Rectangle &in)",         asMETHOD(Rectangle,reduceIfPartlyContainedIn), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Rectangle", "String@ toString()",                                          asMETHOD(asRectangle,toString), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asPath::asPath() {
	refCount = 1;
}
asPath::asPath(const Path &p) :
	path(p), refCount(1) {
}
asPath::asPath(const asPath &p) :
	path(p.path), refCount(1) {
}
asPath::~asPath() {
	jassert( refCount == 0 );
}

int asPath::addRef() {
	return refCount++;
}
int asPath::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asPath& asPath::operator=(const asPath &other) {
	path = other.path;
	return *this;
}

void asPath::getBounds (float* x, float* y, float* width, float* height) {
    path.getBounds (*x, *y, *width, *height);
}

void asPath::getBoundsTransformed (const asAffineTransform& affine, float* x, float* y, float* width, float* height) {
    path.getBoundsTransformed (affine.transform, *x, *y, *width, *height);
}

void asPath::swapWithPath (asPath* other) {
    path.swapWithPath (other->path);
}

asPath* asPath::createPathWithRoundedCorners (const float cornerRadius) {
    return new asPath (path.createPathWithRoundedCorners (cornerRadius));
}

static void ConstructPath(asPath *thisPointer) {
	new(thisPointer) asPath();
}
static void ConstructPathByPath(const asPath& other, asPath *thisPointer) {
    new(thisPointer) asPath(other);
}

void asPath::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Path", sizeof(asPath), asOBJ_CLASS_CDA); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Path", asBEHAVE_CONSTRUCT,  "void f()",                           asFUNCTION(ConstructPath), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Path", asBEHAVE_CONSTRUCT,  "void f(const Path& in)",             asFUNCTION(ConstructPathByPath), asCALL_CDECL_OBJLAST);
	r = engine->RegisterObjectBehaviour("Path", asBEHAVE_ADDREF,     "void f()",                           asMETHOD(asPath,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Path", asBEHAVE_RELEASE,    "void f()",                           asMETHOD(asPath,release), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Path", asBEHAVE_ASSIGNMENT, "Path &f(const Path &in)",            asMETHODPR(asPath, operator=, (const asPath&), asPath&), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Path", "bool isEmpty()",                                                                 asMETHOD(Path,isEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void getBounds(float& out,float& out,float& out, float& out)",                   asMETHOD(asPath,getBounds), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void getBoundsTransformed(const AffineTransform& in,float& out,float& out,float& out,float& out)",  asMETHOD(asPath,getBoundsTransformed), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "bool contains(float,float)",                                                     asMETHOD(Path,contains), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "bool intersectsLine(float,float,float,float)",                                   asMETHOD(Path,intersectsLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void clear()",                                                                   asMETHOD(Path,clear), asCALL_THISCALL);  jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void startNewSubPath(float,float)",                                              asMETHOD(Path,startNewSubPath), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void closeSubPath()",                                                            asMETHOD(Path,closeSubPath), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void lineTo(float,float)",                                                       asMETHOD(Path,lineTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void quadraticTo(float,float,float,float)",                                      asMETHOD(Path,quadraticTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void cubicTo(float,float,float,float,float,float)",                              asMETHOD(Path,cubicTo), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addRectangle(float,float,float,float)",                                     asMETHOD(Path,addRectangle), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void addRoundedRectangle(float,float,float,float,float)",                        asMETHODPR(Path,addRoundedRectangle, (float, float, float, float, float), void), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void addRoundedRectangle(float,float,float,float,float,float)",                  asMETHODPR(Path,addRoundedRectangle, (float, float, float, float, float, float), void), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void addTriangle(float,float,float,float,float,float)",                          asMETHOD(Path,addTriangle), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addQuadrilateral(float,float,float,float,float,float,float,float)",         asMETHOD(Path,addQuadrilateral), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addEllipse(float,float,float,float)",                                       asMETHOD(Path,addEllipse), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addArc(float,float,float,float,float,float,bool)",                          asMETHOD(Path,addArc), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void addCentredArc(float,float,float,float,float,float,float,bool)",             asMETHOD(Path,addCentredArc), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void addPieSegment(float,float,float,float,float,float,float)",                  asMETHOD(Path,addPieSegment), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addLineSegment(float,float,float,float,float)",                             asMETHOD(Path,addLineSegment), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addArrow(float,float,float,float,float,float,float)",                       asMETHOD(Path,addArrow), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addStar(float,float,float,float,float,float)",                              asMETHOD(Path,addStar), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addBubble(float,float,float,float,float,float,float,int,float,float)",      asMETHOD(Path,addBubble), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addPath(const Path& in)",                                                   asMETHODPR(Path,addPath,(const Path&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void addPath(const Path& in,const AffineTransform& in)",                         asMETHODPR(Path,addPath,(const Path&,const AffineTransform&),void), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void swapWithPath(Path& in)",                                                    asMETHOD(asPath,swapWithPath), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Path", "void applyTransform(const AffineTransform& in)",                                 asMETHOD(Path,applyTransform), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void scaleToFit(float,float,float,float,bool)",                                  asMETHOD(Path,scaleToFit), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Path", "AffineTransform@ getTransformToScaleToFit(float,float,float,float,bool,Justification)",      asMETHOD(Path,getTransformToScaleToFit), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "Path@ createPathWithRoundedCorners(float)",                                      asMETHOD(asPath,createPathWithRoundedCorners), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void setUsingNonZeroWinding(bool)",                                              asMETHOD(Path,setUsingNonZeroWinding), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "bool isUsingNonZeroWinding()",                                                   asMETHOD(Path,isUsingNonZeroWinding), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void loadPathFromStream(FileInputStream& in)",                                   asMETHOD(Path,loadPathFromStream), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Path", "void writePathToStream(FileOutputStream& in)",                                   asMETHOD(Path,writePathToStream), asCALL_THISCALL); jassert( r >= 0 );
}


//==============================================================================
asPathStrokeType::asPathStrokeType(const float thickness) :
    stroke (thickness), refCount(1) {}

asPathStrokeType::asPathStrokeType(const PathStrokeType &p) :
    stroke(p), refCount(1) {}

asPathStrokeType::asPathStrokeType(const asPathStrokeType &p) :
    stroke(p.stroke), refCount(1) {}

asPathStrokeType::~asPathStrokeType() {
    jassert( refCount == 0 );
}

int asPathStrokeType::addRef() {
    return refCount++;
}
int asPathStrokeType::release() {
    if( --refCount == 0 ) {
        delete this;
        return 0;
    }
    return refCount;
}

asPathStrokeType& asPathStrokeType::operator=(const asPathStrokeType &other) {
    stroke = other.stroke;
    return *this;
}

bool operator== (const asPathStrokeType& a, const asPathStrokeType& b) { return a.stroke == b.stroke; }
bool operator!= (const asPathStrokeType& a, const asPathStrokeType& b) { return a.stroke != b.stroke; }

static void ConstructPathStrokeType(const float thickness, asPathStrokeType *thisPointer) {
    new(thisPointer) asPathStrokeType(thickness);
}
static void ConstructPathStrokeTypeByRef(const asPathStrokeType& other, asPathStrokeType *thisPointer) {
    new(thisPointer) asPathStrokeType(other.stroke);
}

void asPathStrokeType::registerObjectType(asIScriptEngine *engine)
{
    int r;
    r = engine->RegisterObjectType("PathStrokeType", sizeof(asPathStrokeType), asOBJ_CLASS_CDA); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("PathStrokeType", asBEHAVE_CONSTRUCT,  "void f(const float)",                         asFUNCTION(ConstructPathStrokeType), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("PathStrokeType", asBEHAVE_CONSTRUCT,  "void f(const PathStrokeType &in)",            asFUNCTION(ConstructPathStrokeTypeByRef), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("PathStrokeType", asBEHAVE_ADDREF,     "void f()",                                    asMETHOD(asPathStrokeType,addRef), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("PathStrokeType", asBEHAVE_RELEASE,    "void f()",                                    asMETHOD(asPathStrokeType,release), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("PathStrokeType", asBEHAVE_ASSIGNMENT, "PathStrokeType &f(const PathStrokeType &in)", asMETHODPR(asPathStrokeType, operator=, (const asPathStrokeType&), asPathStrokeType&), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterGlobalBehaviour(asBEHAVE_EQUAL,      "bool f(const PathStrokeType &in, const PathStrokeType &in)",    asFUNCTIONPR(operator==, (const asPathStrokeType &, const asPathStrokeType &), bool), asCALL_CDECL); jassert( r >= 0 );
    r = engine->RegisterGlobalBehaviour(asBEHAVE_NOTEQUAL,   "bool f(const PathStrokeType &in, const PathStrokeType &in)",    asFUNCTIONPR(operator!=, (const asPathStrokeType &, const asPathStrokeType &), bool), asCALL_CDECL); jassert( r >= 0 );

    r = engine->RegisterObjectMethod("PathStrokeType", "float getStrokeThickness()",                                          asMETHOD(PathStrokeType,getStrokeThickness), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("PathStrokeType", "int getJointStyle()",                                                 asMETHOD(PathStrokeType,getJointStyle), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("PathStrokeType", "int getEndStyle()",                                                   asMETHOD(PathStrokeType,getEndStyle), asCALL_THISCALL); jassert( r >= 0 );

    /*

    void createStrokedPath (Path& destPath,
                            const Path& sourcePath,
                            const AffineTransform& transform = AffineTransform::identity,
                            const float extraAccuracy = 1.0f) const;

    const Path createDashedStroke (Path& destPath,
                                   const Path& sourcePath,
                                   const float* dashLengths,
                                   int numDashLengths,
                                   const AffineTransform& transform = AffineTransform::identity) const;

    r = engine->RegisterObjectType("JointStyle_", 0, asOBJ_PRIMITIVE); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("JointStyle_", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("JointStyle_", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectProperty("JointStyle_", "const int mitered",    offsetof(asPathStrokeType,mitered));
    r = engine->RegisterObjectProperty("JointStyle_", "const int curved",     offsetof(asPathStrokeType,curved));
    r = engine->RegisterObjectProperty("JointStyle_", "const int beveled",    offsetof(asPathStrokeType,beveled));
    engine->RegisterGlobalProperty("JointStyle_ JointStyle",(void*)&globalPeer);

    r = engine->RegisterObjectType("EndCapStyle_", 0, asOBJ_PRIMITIVE); jassert( r >= 0 );
    r = engine->RegisterObjectBehaviour("EndCapStyle_", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(dummy_Constructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectBehaviour("EndCapStyle_", asBEHAVE_DESTRUCT,  "void f()", asFUNCTION(dummy_Destructor), asCALL_CDECL_OBJLAST); jassert(r>=0);
    r = engine->RegisterObjectProperty("EndCapStyle_", "const int mitered",    offsetof(asPathStrokeType,butt));
    r = engine->RegisterObjectProperty("EndCapStyle_", "const int curved",     offsetof(asPathStrokeType,square));
    r = engine->RegisterObjectProperty("EndCapStyle_", "const int beveled",    offsetof(asPathStrokeType,rounded));

    */
}



//==============================================================================
asGraphics::asGraphics(Image* imageToDrawOnto) :
	g(*imageToDrawOnto) {
	refCount = 1;
}
asGraphics::asGraphics(asImage* imageToDrawOnto) :
	g(*(imageToDrawOnto->image)) {
	refCount = 1;
}
asGraphics::asGraphics(asImage& imageToDrawOnto) :
	g(*(imageToDrawOnto.image)) {
	refCount = 1;
}
asGraphics::~asGraphics() {
	jassert( refCount == 0 );
}

int asGraphics::addRef() {
	return refCount++;
}
int asGraphics::release() {
	if( --refCount == 0 ) {
		delete this;
		return 0;
	}
	return refCount;
}

asColour* asGraphics::getCurrentColour(){
	return new asColour(g.getCurrentColour());
}
//    void setBrush (Brush* const newBrush);
asFont* asGraphics::getCurrentFont() {
	return new asFont(g.getCurrentFont());
}

// void strokePath (const Path& path,
//                 const PathStrokeType& strokeType,
//                 const AffineTransform& transform = AffineTransform::identity);

void asGraphics::strokePath (const asPath& path, const asAffineTransform& transform) {
	g.strokePath(path.path, PathStrokeType(1.0f), transform.transform);
}

void asGraphics::drawImageAt (const asImage* const imageToDraw,
                  const int topLeftX,
                  const int topLeftY,
                  const bool fillAlphaChannelWithCurrentBrush){
	g.drawImageAt(imageToDraw->image,topLeftX,topLeftY,fillAlphaChannelWithCurrentBrush);
}

void asGraphics::drawImage (const asImage* const imageToDraw,
                int destX,
                int destY,
                int destWidth,
                int destHeight,
                int sourceX,
                int sourceY,
                int sourceWidth,
                int sourceHeight,
                const bool fillAlphaChannelWithCurrentBrush){
	g.drawImage(imageToDraw->image,
					destX,destY,
					destWidth,destHeight,
					sourceX,sourceY,
					sourceWidth,sourceHeight,
					fillAlphaChannelWithCurrentBrush);
}

void asGraphics::drawImageTransformed (const asImage* const imageToDraw,
                           int sourceClipX,
                           int sourceClipY,
                           int sourceClipWidth,
                           int sourceClipHeight,
                           const asAffineTransform& transform,
                           const bool fillAlphaChannelWithCurrentBrush)
{
	g.drawImageTransformed(imageToDraw->image,
					sourceClipX,sourceClipY,
					sourceClipWidth,sourceClipHeight,
					transform.transform,
					fillAlphaChannelWithCurrentBrush);
}

asRectangle* asGraphics::getClipBounds() {
	return new asRectangle(g.getClipBounds());
}

static void ConstructGraphicsByImage(asImage* imageToDrawOnto, asGraphics *thisPointer) {
	new(thisPointer) asGraphics(imageToDrawOnto);
}

void asGraphics::registerObjectType(asIScriptEngine *engine)
{
	int r;
	r = engine->RegisterObjectType("Graphics", sizeof(asGraphics), asOBJ_CLASS_CD); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Graphics", asBEHAVE_CONSTRUCT,  "void f(Image@+)",             asFUNCTION(ConstructGraphicsByImage), asCALL_CDECL_OBJLAST); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Graphics", asBEHAVE_ADDREF,     "void f()",                    asMETHOD(asGraphics,addRef), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectBehaviour("Graphics", asBEHAVE_RELEASE,    "void f()",                    asMETHOD(asGraphics,release), asCALL_THISCALL); jassert( r >= 0 );

	r = engine->RegisterObjectMethod("Graphics", "void setFont(const Font& in)",                                           asMETHODPR(Graphics,setFont,(const Font&),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setFont(float,int)",                                                asMETHODPR(Graphics,setFont,(const float,const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "Font@ getCurrentFont()",                                                 asMETHOD(asGraphics,getCurrentFont), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setColour(const Colour& in)",                                       asMETHOD(Graphics,setColour), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "Colour@ getCurrentColour()",                                             asMETHOD(asGraphics,getCurrentColour), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setPixel(int,int)",                                                 asMETHOD(Graphics,setPixel), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setOpacity(const float)",                                           asMETHOD(Graphics,setOpacity), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setFont(const float,const int)",                                    asMETHODPR(Graphics,setFont,(const float,const int),void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawSingleLineText(const String& in,int,int)",                      asMETHOD(Graphics,drawSingleLineText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawMultiLineText(const String& in,int,int,int)",                   asMETHOD(Graphics,drawMultiLineText), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawTextAsPath(const String& in, const AffineTransform& in)",       asMETHOD(Graphics,drawTextAsPath), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void strokePath(const Path& in, const AffineTransform& in)",             asMETHOD(asGraphics,strokePath), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillPath(const Path& in, const AffineTransform& in)",               asMETHOD(Graphics,fillPath), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillAll()",                                                         asMETHODPR(Graphics,fillAll,(void) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillAll(const Colour& in)",                                         asMETHODPR(Graphics,fillAll,(const Colour&) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillRect(int,int,int,int)",                                         asMETHODPR(Graphics,fillRect,(const int,const int,const int,const int) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillRect(float,float,float,float)",                                 asMETHODPR(Graphics,fillRect,(const float,const float,const float,const float) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillRect(const Rectangle& in)",                                     asMETHODPR(Graphics,fillRect,(const Rectangle&) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillRoundedRectangle(float,float,float,float,float)",               asMETHODPR(Graphics,fillRoundedRectangle, (float, float, float, float, float) const, void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillRoundedRectangle(const Rectangle& in, float)",                  asMETHODPR(Graphics,fillRoundedRectangle, (const Rectangle&, float) const, void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillCheckerBoard(int,int,int,int,int,int,const Colour&,const Colour&)", asMETHOD(Graphics,fillCheckerBoard), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawRect(int,int,int,int,int)",                                     asMETHODPR(Graphics,drawRect, (int, int, int, int, int) const, void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawRect(const Rectangle& in, int)",                                asMETHODPR(Graphics,drawRect, (const Rectangle&, int) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawRoundedRectangle(float,float,float,float,float,float)",         asMETHODPR(Graphics,drawRoundedRectangle, (float, float, float, float, float, float) const, void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawRoundedRectangle(const Rectangle& in,float,float)",             asMETHODPR(Graphics,drawRoundedRectangle, (const Rectangle&, float, float) const, void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawBevel(int,int,int,int,const Colour&in,const Colour&in,bool)",   asMETHOD(Graphics,drawBevel), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void fillEllipse(float,float,float,float)",                              asMETHOD(Graphics,fillEllipse), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawEllipse(float,float,float,float,float)",                        asMETHOD(Graphics,drawEllipse), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawLine(float,float,float,float)",                                 asMETHODPR(Graphics,drawLine,(const float,const float,const float,const float) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawLine(float,float,float,float,float)",                           asMETHODPR(Graphics,drawLine,(const float,const float,const float,const float,const float) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawLine(const Line& line)",                                        asMETHODPR(Graphics,drawLine,(const Line&) const,void), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawLine(const Line& line,float)",                                  asMETHODPR(Graphics,drawLine,(const Line&,const float) const,void), asCALL_THISCALL); jassert( r >= 0 );
//	r = engine->RegisterObjectMethod("Graphics", "void drawDashedLine(float,float,float,float,float[],int,float)",         asMETHOD(asGraphics,drawDashedLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawVerticalLine(int,float,float)",                                 asMETHOD(Graphics,drawVerticalLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawHorizontalLine(int,float,float)",                               asMETHOD(Graphics,drawHorizontalLine), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawArrow(float,float,float,float,float,float,float)",              asMETHOD(Graphics,drawArrow), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawImageAt(Image@+,int,int,bool)",                                 asMETHOD(asGraphics,drawImageAt), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawImage(Image@+,int,int,int,int,int,int,int,int,bool)",           asMETHOD(asGraphics,drawImage), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void drawImageTransformed(Image@+,int,int,int,int,const AffineTransform& in,bool)", asMETHOD(asGraphics,drawImageTransformed), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void saveState()",                                                       asMETHOD(Graphics,saveState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void restoreState()",                                                    asMETHOD(Graphics,restoreState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "Rectangle@ getClipBounds()",                                             asMETHOD(asGraphics,getClipBounds), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "bool clipRegionIntersects(int,int,int,int)",                             asMETHOD(Graphics,clipRegionIntersects), asCALL_THISCALL); jassert( r >= 0 );
    r = engine->RegisterObjectMethod("Graphics", "bool reduceClipRegion(int,int,int,int)",                                 asMETHODPR(Graphics,reduceClipRegion,(const int,const int,const int,const int), bool), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void excludeClipRegion(int,int,int,int)",                                asMETHOD(Graphics,excludeClipRegion), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "bool isClipEmpty()",                                                     asMETHOD(Graphics,isClipEmpty), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void setOrigin(int,int)",                                                asMETHOD(Graphics,setOrigin), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "void resetToDefaultState()",                                             asMETHOD(Graphics,resetToDefaultState), asCALL_THISCALL); jassert( r >= 0 );
	r = engine->RegisterObjectMethod("Graphics", "bool isVectorDevice()",                                                  asMETHOD(Graphics,isVectorDevice), asCALL_THISCALL); jassert( r >= 0 );
}

