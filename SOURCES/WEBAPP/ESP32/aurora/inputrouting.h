#ifndef _INPUTROUTING_H_
#define _INPUTROUTING_H_

static const int kNumSourceNames = 8;

extern int currentVirtualInput;

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
void handlePostInputRoutingJson(AsyncWebServerRequest *request, uint8_t *data);

//==============================================================================
/*! Handles the GET request for virtual input selection
 *
 */
void handleGetVirtualInputJson(AsyncWebServerRequest *request);

//==============================================================================
/*! Handles the POST request for virtual input selection
 *
 */
void handlePostVirtualInputJson(AsyncWebServerRequest *request, uint8_t *data);

//==============================================================================
/*! Saves the current assignment virtual <-> physical input
 *
 */
bool writeVirtualInputRouting(void);

//==============================================================================
/*! Reads the saved assignment virtual <-> physical input from file
 *
 */
bool readVirtualInputRouting(void);

//==============================================================================
/*! Sets the virtual input routing for current selection
 *
 */
void setVirtualInput(void);

//==============================================================================
/*! Selects the next virtual input by incrementing
 *
 */
void incrementVirtualInput(void);

//==============================================================================
/*! Selects the next virtual input by decrementing
 *
 */
void decrementVirtualInput(void);

#endif
