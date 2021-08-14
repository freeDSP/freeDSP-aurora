#ifndef _INPUTROUTING_H_
#define _INPUTROUTING_H_

//==============================================================================
/*! Builds the HTML page for the input routing by source names.
 *
 */
String createInputRoutingPage(int numinputs);

//==============================================================================
/*! Handles the GET request for input routing
 *
 */
String handleGetInputRoutingJson(void/*AsyncWebServerRequest* request*/);

//==============================================================================
/*! Handles the POST request for input routing
 *
 */
void handlePostInputRoutingJson(AsyncWebServerRequest* request, uint8_t* data);

//==============================================================================
/*! Handles the GET request for virtual input selection
 *
 */
void handleGetVirtualInputJson(AsyncWebServerRequest* request);

//==============================================================================
/*! Handles the POST request for virtual input selection
 *
 */
void handlePostVirtualInputJson(AsyncWebServerRequest* request, uint8_t* data);

#endif
