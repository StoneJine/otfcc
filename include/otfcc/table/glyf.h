#ifndef CARYLL_INCLUDE_TABLE_GLYF_H
#define CARYLL_INCLUDE_TABLE_GLYF_H

#include "table-common.h"
#include "head.h"
#include "maxp.h"

enum GlyphType { SIMPLE, COMPOSITE };

typedef struct {
	pos_t x;
	pos_t y;
	int8_t onCurve; // a mask indicates whether a point is on-curve or off-curve
	                // bit 0     : 1 for on-curve, 0 for off-curve. JSON field: "on"
	                // bit 1 - 7 : unused, set to 0
	                // in JSON, they are separated into several boolean fields.
} glyf_Point;
extern caryll_ElementInterface(glyf_Point) glyf_iPoint;
typedef caryll_Vector(glyf_Point) glyf_Contour;
extern caryll_VectorInterface(glyf_Contour, glyf_Point) glyf_iContour;

typedef caryll_Vector(glyf_Contour) glyf_ContourList;
extern caryll_VectorInterface(glyf_ContourList, glyf_Contour) glyf_iContourList;

// CFF stems and hint masks
typedef struct {
	pos_t position;
	pos_t width;
	uint16_t map;
} glyf_PostscriptStemDef;
extern caryll_ElementInterface(glyf_PostscriptStemDef) glyf_iPostscriptStemDef;
typedef caryll_Vector(glyf_PostscriptStemDef) glyf_StemDefList;
extern caryll_VectorInterface(glyf_StemDefList, glyf_PostscriptStemDef) glyf_iStemDefList;

typedef struct {
	uint16_t pointsBefore;
	uint16_t contoursBefore;
	bool maskH[0x100];
	bool maskV[0x100];
} glyf_PostscriptHintMask;
extern caryll_ElementInterface(glyf_PostscriptHintMask) glyf_iPostscriptHintMask;
typedef caryll_Vector(glyf_PostscriptHintMask) glyf_MaskList;
extern caryll_VectorInterface(glyf_MaskList, glyf_PostscriptHintMask) glyf_iMaskList;

typedef enum {
	REF_XY = 0,
	REF_ANCHOR_ANCHOR = 1,
	REF_ANCHOR_XY = 2,
	REF_ANCHOR_CONSOLIDATED = 3,
	REF_ANCHOR_CONSOLIDATING_ANCHOR = 4,
	REF_ANCHOR_CONSOLIDATING_XY = 5,
} RefAnchorStatus;

typedef struct {
	otfcc_GlyphHandle glyph;
	// transformation term
	pos_t a;
	pos_t b;
	pos_t c;
	pos_t d;
	// position term
	RefAnchorStatus isAnchored;
	shapeid_t inner;
	shapeid_t outer;
	pos_t x;
	pos_t y;
	// flags
	bool roundToGrid;
	bool useMyMetrics;
} glyf_ComponentReference;
extern caryll_ValElementInterface(glyf_ComponentReference) glyf_iComponentReference;
typedef caryll_Vector(glyf_ComponentReference) glyf_ReferenceList;
extern caryll_VectorInterface(glyf_ReferenceList, glyf_ComponentReference) glyf_iReferenceList;

typedef struct {
	pos_t xMin;
	pos_t xMax;
	pos_t yMin;
	pos_t yMax;
	uint16_t nestDepth;
	uint16_t nPoints;
	uint16_t nContours;
	uint16_t nCompositePoints;
	uint16_t nCompositeContours;
} glyf_GlyphStat;

typedef struct {
	sds name;

	// Metrics
	pos_t horizontalOrigin;
	length_t advanceWidth;
	pos_t verticalOrigin;
	length_t advanceHeight;

	// Outline
	// NOTE: SFNT does not support mixed glyphs, but we do.
	OWNING glyf_ContourList contours;
	OWNING glyf_ReferenceList references;

	// Postscript hints
	OWNING glyf_StemDefList stemH;
	OWNING glyf_StemDefList stemV;
	OWNING glyf_MaskList hintMasks;
	OWNING glyf_MaskList contourMasks;

	// TTF instructions
	uint16_t instructionsLength;
	uint8_t *instructions;
	// TTF Screen specific
	uint8_t yPel;

	// CID FDSelect
	otfcc_FDHandle fdSelect;

	// Stats
	glyf_GlyphStat stat;
} glyf_Glyph;

typedef glyf_Glyph *glyf_GlyphPtr;
extern caryll_ElementInterface(glyf_GlyphPtr) glyf_iGlyphPtr;
typedef caryll_Vector(glyf_GlyphPtr) table_glyf;
extern caryll_VectorInterface(table_glyf, glyf_GlyphPtr) table_iGlyf;

#endif
