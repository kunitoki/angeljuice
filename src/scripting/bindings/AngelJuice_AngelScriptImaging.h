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

#ifndef __ANGELJUICE_ANGELSCRIPTIMAGING_HEADER__
#define __ANGELJUICE_ANGELSCRIPTIMAGING_HEADER__

#include "juce.h"

class asString;


//==============================================================================
/** Manages colors in angel scripts

    @see AngelScriptEngine, Colour
*/
class asColour
{
public:

	asColour();
	asColour(int rgba);
	asColour(int red, int green, int blue, int alpha);
	asColour(float red, float green, float blue, float alpha);
	asColour(const Colour& other);
	asColour(const asColour& other);

	int addRef();
	int release();

	void getHSB (float* hue,float* saturation,float* brightness);
    asColour* withAlpha (const uint8 newAlpha);
    asColour* withAlpha (const float newAlpha);
    asColour* withMultipliedAlpha (const float alphaMultiplier);
    asColour* overlaidWith (const asColour& foregroundColour);
    asColour* withHue (const float newHue);
    asColour* withSaturation (const float newSaturation);
    asColour* withBrightness (const float newBrightness);
    asColour* withRotatedHue (const float amountToRotate);
    asColour* withMultipliedSaturation (const float multiplier);
    asColour* withMultipliedBrightness (const float amount);
	asColour* brighter (float amountBrighter = 0.4f);
    asColour* darker (float amountDarker = 0.4f);
    asColour* contrasting (const float amount = 1.0f);
    //	static asColour* contrasting (const Colour& colour1, const Colour& colour2);
    //  static asColour* greyLevel (const float brightness);
    //  const PixelARGB getPixelARGB();

    asColour& operator= (const asColour& other);

    static void registerObjectType(asIScriptEngine *engine);

	Colour col;

protected:
    friend class asColours;
	asColour(const Colour& other, int refCount);

	~asColour();
	int refCount;
};

/*
class asColours
{
public:

    asColours ();

//    static asColour* findColourForName(const asString& name, const asColour& def);

    asColour
        transparentBlack,       transparentWhite,
        black,                  white,              blue,
        grey,                   green,              red,                yellow,
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
};
*/

//==============================================================================
/** Manages images in angel scripts

    @see AngelScriptEngine, Image
*/
class asImage
{
public:

	asImage(int imageWidth, int imageHeight);
	asImage(const Image& other);
	asImage(const asImage& other);
	asImage(Image* other);
	asImage(asImage* other);

	int addRef();
	int release();

    int getWidth();
    int getHeight();
    bool isARGB();
    bool isRGB();
    bool hasAlphaChannel();
	void clear (int x, int y, int w, int h, const asColour& colourToClearTo);
    asImage* createCopy (int newWidth, int newHeight);
	asColour* getPixelAt (const int x, const int y);
    void setPixelAt (const int x, const int y, const asColour& colour);
    void multiplyAlphaAt (const int x, const int y, const float multiplier);
    void multiplyAllAlphas (const float amountToMultiplyBy);
    void desaturate ();
    void moveImageSection (int destX, int destY, int sourceX, int sourceY, int width, int height);

//	uint8* lockPixelDataReadWrite (int x, int y, int w, int h, int* lineStride, int* pixelStride);
	asIScriptArray* lockPixelDataReadWrite (int x, int y, int w, int h, int* lineStride, int* pixelStride);
    void releasePixelDataReadWrite ();
    //  const uint8* lockPixelDataReadOnly (int x, int y, int w, int h, int& lineStride, int& pixelStride);
    //  void releasePixelDataReadOnly (const void* sourceData);
    //  void setPixelData (int destX, int destY, int destW, int destH, const uint8* sourcePixelData, int sourceLineStride);

	static void registerObjectType(asIScriptEngine *engine);

	Image* image;

protected:
	~asImage();
	int refCount;
};


//==============================================================================
/** Manages images convolution kernels in angel scripts

    @see AngelScriptEngine, Image
 */
class asImageConvolutionKernel
{
public:

    asImageConvolutionKernel(const int size);

    int addRef();
    int release();

    void applyToImage (asImage* destImage,
                       asImage* sourceImage,
                       int x,
                       int y,
                       int width,
                       int height);

    static void registerObjectType(asIScriptEngine *engine);

    ImageConvolutionKernel kernel;

protected:
    ~asImageConvolutionKernel();
    int refCount;
};



//==============================================================================
/** Manages fonts in angel scripts

    @see AngelScriptEngine, Font
*/
class asFont
{
public:

    asFont();
    asFont (const float fontHeight, const int styleFlags);
    asFont (const Font& other);
    asFont (const asFont& other);

	int addRef();
	int release();

    asString* getTypefaceName();

    //    static const String getDefaultSansSerifFontName();
    //    static const String getDefaultSerifFontName();
    //    static const String getDefaultMonospacedFontName();
    //    static void setDefaultSansSerifFontName (const asString& name);
    //    Typeface* getTypeface() const;

    const asFont& operator= (const asFont& other);

	static void registerObjectType(asIScriptEngine *engine);

	Font font;

	int plain;      // = 0
	int bold;       // = 1
	int italic;     // = 2
	int underlined; // = 4

protected:
	~asFont();
	int refCount;
};


//==============================================================================
/** Manages affine transformations in angel scripts

    @see AngelScriptEngine, AffineTransform
*/
class asAffineTransform
{
public:

	asAffineTransform();
	asAffineTransform(const AffineTransform& other);
	asAffineTransform(const asAffineTransform& other);

	int addRef();
	int release();

    void transformPoint (float* x, float* y);
    asAffineTransform& translated (float deltaX, float deltaY);
    asAffineTransform& rotated (float angleInRadians);
    asAffineTransform& rotated (float angleInRadians, float pivotX, float pivotY);
    asAffineTransform& scaled (float factorX, float factorY);
    asAffineTransform& sheared (float shearX, float shearY);
    asAffineTransform& inverted();
    asAffineTransform& followedBy (const asAffineTransform& other);

    asAffineTransform& operator=(const asAffineTransform &other);

    static void registerObjectType(asIScriptEngine *engine);

	AffineTransform transform;

protected:
	~asAffineTransform();
	int refCount;
};


//==============================================================================
/** Manages bidimensional points in angel scripts

    @see AngelScriptEngine, Point
*/
class asPoint
{
public:

	asPoint();
	asPoint(float x, float y);
	asPoint(const Point& other);
	asPoint(const asPoint& other);

	int addRef();
	int release();

	asPoint& operator=(const asPoint &other);

	static void registerObjectType(asIScriptEngine *engine);

	Point point;

protected:
	~asPoint();
	int refCount;
};


//==============================================================================
/** Manages bidimensional lines in angel scripts

    @see AngelScriptEngine, Line
*/
class asLine
{
public:

	asLine();
	asLine(float startX,float startY,float endX,float endY);
	asLine(const Line& other);
	asLine(const asLine& other);
	asLine(const asPoint& start,const asPoint& end);

	int addRef();
	int release();

	asPoint* getStart();
	asPoint* getEnd();
	asPoint* getPointAlongLine (float distanceFromStart);
	asPoint* getPointAlongLine (float distanceFromStart, float perpendicularDistance);
	asPoint* getPointAlongLineProportionally (float proportionOfLength);
	asLine* withShortenedStart (float distanceToShortenBy);
	asLine* withShortenedEnd (float distanceToShortenBy);
	bool intersects(const asLine& in, float* x, float* y);

    asLine& operator=(const asLine &other);

	static void registerObjectType(asIScriptEngine *engine);

	Line line;

protected:
	~asLine();
	int refCount;
};


//==============================================================================
/** Manages bidimensional rectangles in angel scripts

    @see AngelScriptEngine, Rectangle
*/
class asRectangle
{
public:

	asRectangle();
	asRectangle(int x, int y, int w, int h);
	asRectangle(const Rectangle& other);
	asRectangle(const asRectangle& other);

	int addRef();
	int release();

    asRectangle* translated (int deltaX, int deltaY);
    asRectangle* expanded (int deltaX, int deltaY);
    asRectangle* getIntersection (const asRectangle& other);
    asRectangle* getUnion (const asRectangle& other);
	bool intersectRectangle (int* x, int* y, int* w, int* h);
//    static bool intersectRectangles (int& x1, int& y1, int& w1, int& h1, int x2, int y2, int w2, int h2);
//	  asString* toString();
//    static const Rectangle fromString (const String& stringVersion);

    asRectangle& operator=(const asRectangle &other);

	static void registerObjectType(asIScriptEngine *engine);

	Rectangle rect;

protected:
	~asRectangle();
	int refCount;
};


//==============================================================================
/** Manages paths in angel scripts

    @see AngelScriptEngine, Path
*/
class asPath
{
public:

	asPath();
	asPath(const Path& other);
	asPath(const asPath& other);

	int addRef();
	int release();

    void getBounds (float* x, float* y, float* width, float* height);
    void getBoundsTransformed (const asAffineTransform& affine,
                               float* x,
                               float* y,
                               float* width,
                               float* height);
    void swapWithPath (asPath* other);
    asPath* createPathWithRoundedCorners (const float cornerRadius);

    asPath& operator=(const asPath &other);

	static void registerObjectType(asIScriptEngine *engine);

	Path path;

protected:
	~asPath();
	int refCount;
};


//==============================================================================
/** Manages paths stroke style in angel scripts

    @see AngelScriptEngine, Path, PathStrokeType
 */
class asPathStrokeType
{
public:

    asPathStrokeType(const float thickness);
    asPathStrokeType(const PathStrokeType& other);
    asPathStrokeType(const asPathStrokeType& other);

    int addRef();
    int release();

    asPathStrokeType& operator=(const asPathStrokeType &other);

    static void registerObjectType(asIScriptEngine *engine);

    PathStrokeType stroke;

protected:
    ~asPathStrokeType();
    int refCount;
};


//==============================================================================
/** Manages graphics in angel scripts

    @see AngelScriptEngine, Graphics
*/
class asGraphics
{
public:

    asGraphics (Image* imageToDrawOnto);
    asGraphics (asImage* imageToDrawOnto);
    asGraphics (asImage& imageToDrawOnto);

	int addRef();
	int release();

    asColour* getCurrentColour();
    asFont* getCurrentFont();
//    void setBrush (Brush* const newBrush);

/*
	void drawText (const String& text,
                   const int x,
                   const int y,
                   const int width,
                   const int height,
                   const Justification& justificationType,
                   const bool useEllipsesIfTooBig);
	void drawFittedText (const String& text,
                         const int x,
                         const int y,
                         const int width,
                         const int height,
                         const Justification& justificationFlags,
                         const int maximumNumberOfLines);
*/

	void strokePath (const asPath& path, const asAffineTransform& transform);
//    void strokePath (const Path& path,
//                     const PathStrokeType& strokeType,
//                     const AffineTransform& transform = AffineTransform::identity);

//    void setImageResamplingQuality (const ResamplingQuality newQuality);
    void drawImageAt (const asImage* const imageToDraw,
                      const int topLeftX,
                      const int topLeftY,
                      const bool fillAlphaChannelWithCurrentBrush);

    void drawImage (const asImage* const imageToDraw,
                    int destX,
                    int destY,
                    int destWidth,
                    int destHeight,
                    int sourceX,
                    int sourceY,
                    int sourceWidth,
                    int sourceHeight,
                    const bool fillAlphaChannelWithCurrentBrush);

    void drawImageTransformed (const asImage* const imageToDraw,
                               int sourceClipX,
                               int sourceClipY,
                               int sourceClipWidth,
                               int sourceClipHeight,
                               const asAffineTransform& transform,
                               const bool fillAlphaChannelWithCurrentBrush);
/*
	void drawImageWithin (const Image* const imageToDraw,
                          const int destX,
                          const int destY,
                          const int destWidth,
                          const int destHeight,
                          const Justification& placementWithinTarget,
                          const bool onlyReduceInSize,
                          const bool fillAlphaChannelWithCurrentBrush);
*/
	asRectangle* getClipBounds();
    bool clipRegionIntersects (const int x, const int y, const int width, const int height);
    bool reduceClipRegion (const int x, const int y, const int width, const int height);
    void excludeClipRegion (const int x, const int y, const int width, const int height);
    bool isClipEmpty();
//    const RectangleList getClipRegion() const;
//    void setClipRegion (const RectangleList& newRegion);
    void setOrigin (const int newOriginX,const int newOriginY);
    void resetToDefaultState();



	static void registerObjectType(asIScriptEngine *engine);

	Graphics g;

protected:
	~asGraphics();
	int refCount;

private:
	asGraphics (const asGraphics&);
};


#endif	// __ANGELJUICE_ANGELSCRIPTIMAGING_HEADER__
