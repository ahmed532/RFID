//SEE README in the snarc/server/ folder for how to use this script with google docs.
// The onOpen function is executed automatically every time a Spreadsheet is loaded
function onOpen() {  
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var menuEntries = [];
  // When the user clicks on "addMenuExample" then "Menu Entry 1", the function function1 is executed.
  menuEntries.push({name: "Do it Now!", functionName: "report_to_space_server"});
 // menuEntries.push(null); // line separator
 // menuEntries.push({name: "Send reminder", functionName: "sendEmailReminder"});
  ss.addMenu("Report to Auth Server! ", menuEntries);
}
// there is a "trigger" configured to run this function whenever the spreadsheed is edited See Triggers->Current etc 
function report_to_auth_server() { 
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Sheet1");
  var numRows = sheet.getLastRow()+1;
  // getRange:  row, column, optNumRows, optNumColumns   
  var dataSelection = sheet.getRange(2, 1, numRows-2, 2).getValues(); // get data in first two columns only, as a 2d javascript array
//  var payload =  array2dToJson(dataSelection, 'payload', '\n');
 var json =  Utilities.jsonStringify(dataSelection);
 var secret = "somethingsecret"; // a secret string representing a fixed password. 
  //Browser.msgBox(payload);
 var payload = "json="+json+"&secret="+secret;
  var advancedArgs = { contentType:'application/x-www-form-urlencoded', method:'POST', payload:payload } ; 
 //Browser.msgBox(Utilities.jsonStringify(advancedArgs));
  
// The code below shows the HTML code of the Google home page.
var response = UrlFetchApp.fetch("https://your.auth.server/doorupdate.php", advancedArgs);

  // for debugging.   in reality,  just doing the HTTP get should be enough to tell the space server to pull the docs content down to itself.  
Browser.msgBox(response.getContentText());
} 

