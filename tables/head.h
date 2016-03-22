#ifndef CARYLL_TABLES_HEAD_H
#define CARYLL_TABLES_HEAD_H

#include <stdint.h>
#include "../caryll-font.h"
#include "../extern/parson.h"

typedef struct {
	// Font header
	uint32_t version;
	uint32_t fontRevison;
	uint32_t checkSumAdjustment;
	uint32_t magicNumber;
	uint16_t flags;
	uint16_t unitsPerEm;
	int64_t created;
	int64_t modified;
	int16_t xMin;
	int16_t yMin;
	int16_t xMax;
	int16_t yMax;
	uint16_t macStyle;
	uint16_t lowestRecPPEM;
	int16_t fontDirectoryHint;
	int16_t indexToLocFormat;
	int16_t glyphDataFormat;
} table_head;

void caryll_read_head(caryll_font *font, caryll_packet packet);
void caryll_head_to_json(caryll_font *font, JSON_Object *root);

#endif