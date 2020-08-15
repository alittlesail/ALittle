
#include <SDL.h>
#include <SDL_syswm.h>

#ifdef __IPHONEOS__

#ifndef _ALITTLE_IOSDELEGATE_H_
#define _ALITTLE_IOSDELEGATE_H_

#import <UIKit/UIKit.h>

#import <UIKit/UIApplication.h>

@class Reachability;

@interface iOSReachabilityDelegate : NSObject <UIApplicationDelegate>
{
    Reachability* hostReach;
}

- (void)Init;

- (void)StartNotify;

@end

@interface iOSWebViewDelegate : NSObject <UIWebViewDelegate>
{
}

- (BOOL)webView:(UIWebView*)webView shouldStartLoadWithRequest:(NSURLRequest*)request navigationType:(UIWebViewNavigationType)navigationType;
+(NSString*)DataTOjsonString : (NSDictionary*)object;

@end

#import <Photos/Photos.h>
@interface iOSAlbumManager : NSObject <UINavigationControllerDelegate, UIImagePickerControllerDelegate>
{
}

- (bool)openAlbum;
- (void)imagePickerController : (UIImagePickerController*)picker didFinishPickingMediaWithInfo : (NSDictionary*)info;
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker;
+ (UIImage *)fixOrientation:(UIImage *)image;
- (SDL_Surface*)getPhoto : (const char*)file_path;

@end

#endif
#endif
