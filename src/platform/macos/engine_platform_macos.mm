#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "Engine.h"

using namespace Engine;

EVector<EString> Platform::OpenFileDialog(const EString& title, const EVector<EString>& filters, const EString& defaultPath) 
{
   int i;
   EVector<EString> fileList;
   // Create a File Open Dialog class.
   NSOpenPanel* openDlg = [NSOpenPanel openPanel];
   [openDlg setLevel:CGShieldingWindowLevel()];
   // Set array of file types

   NSMutableArray * fileTypesArray = [NSMutableArray array];
   for (i = 0;i < filters.size(); i++)
   {
      NSString * filt =[NSString stringWithUTF8String:filters[i].c_str()];
      [fileTypesArray addObject:filt];
   }

   // Enable options in the dialog.
   [openDlg setCanChooseFiles:YES];
   [openDlg setAllowedFileTypes:fileTypesArray];
   [openDlg setAllowsMultipleSelection:TRUE];
   [openDlg setDirectoryURL:[NSURL URLWithString:[NSString stringWithUTF8String:defaultPath.c_str() ] ] ];

   // Display the dialog box. If the OK pressed,
   // process the files.
   if ( [openDlg runModal] == NSModalResponseOK ) {
      // Gets list of all files selected
      NSArray *files = [openDlg URLs];
      // Loop through the files and process them.
      for( i = 0; i < [files count]; i++ ) {
         // Do something with the filename.
        fileList.push_back(std::string([[[files objectAtIndex:i] path] UTF8String]));
         }
      }
   return fileList;
}