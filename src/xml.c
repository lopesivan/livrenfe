/* Copyright (c) 2016 Pablo G. Gallardo <pggllrd@gmail.com>
 *
 * This file is part of LivreNFE.
 *
 * LivreNFE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LivreNFE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LivreNFE.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "xml.h"
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <string.h>
#include <stdlib.h>

static xmlXPathObjectPtr getnodeset(xmlDocPtr doc, xmlChar *xpath){
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;

	context = xmlXPathNewContext(doc);
	if (context == NULL) {
		printf("Error in xmlXPathNewContext\n");
		return NULL;
	}
	result = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		printf("Error in xmlXPathEvalExpression\n");
		return NULL;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
                printf("No result\n");
		return NULL;
	}
	return result;
}

char *get_xml_element(xmlDocPtr doc, char *element){
	char *xpath = malloc(sizeof(char) * strlen(element) + 3);
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;
	strcpy(xpath, "//");
	strcat(xpath, element);
	xmlChar *content;

	result = getnodeset(doc, xpath);
	if(result) {
		nodeset = result->nodesetval;
		content = xmlNodeListGetString(doc, 
			nodeset->nodeTab[0]->xmlChildrenNode, 1);
	}
	free(xpath);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return content;
}