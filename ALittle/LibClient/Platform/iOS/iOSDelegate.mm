
#include <SDL.h>

#ifdef __IPHONEOS__

#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"

#import "iOSDelegate.h"
#import "Reachability.h"
#import "iOSSystem.h"

@implementation iOSReachabilityDelegate

- (void)reachabilityChanged : (NSNotification*)note
{
    Reachability* curReach = [note object];
    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
    NetworkStatus status = [curReach currentReachabilityStatus];
    
    if (status == NotReachable)
	    g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_NetworkChanged", -1, "OtherSystem_NotifyNetwork_none", -1);
    else if (status == ReachableViaWWAN)
        g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_NetworkChanged", -1, "OtherSystem_NotifyNetwork_line", -1);
    else if (status == ReachableViaWiFi)
        g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_NetworkChanged", -1, "OtherSystem_NotifyNetwork_wifi", -1);
}

- (void)Init
{
    hostReach = nil;
}

- (void)StartNotify
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                          selector:@selector(reachabilityChanged:)
                                          name: kReachabilityChangedNotification
                                          object: nil];
    hostReach = [[Reachability reachabilityWithHostName:@"www.apple.com"] retain];
    [hostReach startNotifier];
}

@end


@implementation iOSWebViewDelegate

- (BOOL)webView:(UIWebView*)webView shouldStartLoadWithRequest : (NSURLRequest*)request navigationType : (UIWebViewNavigationType)navigationType
{
    NSString* url = [[[request URL]  absoluteString] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    NSArray* url_list = [url componentsSeparatedByString:@"://"];
    if ([url_list count] == 2 && [[url_list objectAtIndex:0] isEqualToString:@"ALittle"])
    {
        NSString* content = [url_list objectAtIndex:1];
        g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_ALittleJsonRPC", -1, (char*)[content UTF8String], -1);
        return NO;
    }
    return YES;
}

-(void)webViewDidStartLoad : (UIWebView*)webView
{

}

-(void)webViewDidFinishLoad : (UIWebView*)webView
{
    // 取消长按webView上的链接弹出actionSheet的问题
    // [webView stringByEvaluatingJavaScriptFromString:@"document.documentElement.style.webkitTouchCallout = 'none';"]；

    NSString* theTitle=[webView stringByEvaluatingJavaScriptFromString:@"document.title"]; 
    NSDictionary* json = @{@"id" : @"id", @"title" : theTitle};
    NSString* param = [iOSWebViewDelegate DataTOjsonString: json];
    const char* content = [param UTF8String];
    g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_WebPageFinished", -1, content, -1);
}

-(void)webView:(UIWebView*)webView DidFailLoadWithError:(NSError*)error
{
    NSDictionary* json = @{@"id" : @"id", @"error" : error};
    NSString* param = [iOSWebViewDelegate DataTOjsonString: json];
    const char* content = [param UTF8String];
    g_ScheduleSystem.PushExternalEvent("__ALITTLEAPI_WebReceivedError", -1, content, -1);
}

+ (NSString*)DataTOjsonString : (NSDictionary*)object
{  
    NSString* jsonString = nil;  
    NSError* error;  
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:object options:NSJSONWritingPrettyPrinted error:&error];  
    if (jsonData) jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    return jsonString;  
}

@end

@implementation iOSAlbumManager

- (bool)openAlbum
{
    // 设备不可用  直接返回
    if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypePhotoLibrary]) return false;

    UIImagePickerController* img_picker = [[UIImagePickerController alloc] init];
    img_picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    img_picker.delegate = self;
    
    const SDL_SysWMinfo& main_syswm_info = g_RenderSystem.GetSysWMinfo();
    UIViewController* main_view_controller = main_syswm_info.info.uikit.window.rootViewController;
    [main_view_controller presentViewController:img_picker animated:YES completion:nil];
    return true;
}

// 选择照片之后
- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary*)info
{
    // 获取用户选择的图片
    NSURL* url = [info objectForKey:@"UIImagePickerControllerImageURL"];
    if (!url) url = [info objectForKey:@"UIImagePickerControllerReferenceURL"];
    std::string path;
    if (url)
    {
        NSString* tmp = [url absoluteString];
        path = [tmp UTF8String];
    }
    g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSelectFile", path.c_str());

    // 退出imagePickerController
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController*)picker
{
    // 退出imagePickerController
    [picker dismissViewControllerAnimated:YES completion:nil];
    
    g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSelectFile", "");
}

+ (UIImage *)fixOrientation:(UIImage*)image
{   
    // No-op if the orientation is already correct
    if (image.imageOrientation == UIImageOrientationUp) 
        return image;
    
    // We need to calculate the proper transformation to make the image upright.
    // We do it in 2 steps: Rotate if Left/Right/Down, and then flip if Mirrored.
    CGAffineTransform transform = CGAffineTransformIdentity;
    
    switch (image.imageOrientation) {
        case UIImageOrientationDown:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, image.size.height);
            transform = CGAffineTransformRotate(transform, M_PI);
            break;
            
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, 0);
            transform = CGAffineTransformRotate(transform, M_PI_2);
            break;
            
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, 0, image.size.height);
            transform = CGAffineTransformRotate(transform, -M_PI_2);
            break;
        default:
            break;
    }
    
    switch (image.imageOrientation) {
        case UIImageOrientationUpMirrored:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
            
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.height, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
        default:
            break;
    }
    
    // Now we draw the underlying CGImage into a new context, applying the transform
    // calculated above.
    CGContextRef ctx = CGBitmapContextCreate(NULL, image.size.width, image.size.height,
                                             CGImageGetBitsPerComponent(image.CGImage), 0,
                                             CGImageGetColorSpace(image.CGImage),
                                             CGImageGetBitmapInfo(image.CGImage));
    CGContextConcatCTM(ctx, transform);
    switch (image.imageOrientation) {
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            // Grr...
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.height,image.size.width), image.CGImage);
            break;
            
        default:
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.width,image.size.height), image.CGImage);
            break;
    }
    
    // And now we just create a new UIImage from the drawing context
    CGImageRef cgimg = CGBitmapContextCreateImage(ctx);
    UIImage* img = [UIImage imageWithCGImage:cgimg];
    CGContextRelease(ctx);
    CGImageRelease(cgimg);
    return img;
}

- (SDL_Surface*)getPhoto:(const char*)file_path
{
    // 转为NSURL
    NSURL* url = [NSURL URLWithString:[NSString stringWithUTF8String:file_path]];
    if (!url) return 0;
    
    __block UIImage* image = 0;
    
    std::string str_file_path = file_path;
    if (str_file_path.find("assets-library://") == 0)
    {
        PHFetchResult * fetchResult = [PHAsset fetchAssetsWithALAssetURLs: @ [url] options: nil];
        PHAsset * asset = fetchResult.firstObject;
        PHImageManager *manager = [PHImageManager defaultManager];
        PHImageRequestOptions * imageRequestOptions = [[PHImageRequestOptions alloc] init];
        [imageRequestOptions setSynchronous:TRUE];
        [manager requestImageForAsset:asset targetSize:PHImageManagerMaximumSize contentMode:PHImageContentModeDefault options:imageRequestOptions resultHandler:^(UIImage *resultImage, NSDictionary *info)
        {
            image = resultImage;
        }];
    }
    // 从url中获取UIImage
    else
        image = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    if (image == 0) return 0;
    image = [iOSAlbumManager fixOrientation:image];
    
    CGImageRef image_ref = image.CGImage;
    size_t w = CGImageGetWidth(image_ref);
    size_t h = CGImageGetHeight(image_ref);
    CGRect rect = CGRectMake(0, 0, w ,h);
    CGImageAlphaInfo alpha = CGImageGetAlphaInfo(image_ref);
    size_t bits_per_component = 8;
        
    Uint32 Amask;
    Uint32 Rmask;
    Uint32 Gmask;
    Uint32 Bmask;
        
    CGContextRef bitmap_context;
    CGBitmapInfo bitmap_info;
    CGColorSpaceRef color_space = CGColorSpaceCreateDeviceRGB();
        
    if (alpha == kCGImageAlphaNone ||
        alpha == kCGImageAlphaNoneSkipFirst ||
        alpha == kCGImageAlphaNoneSkipLast) {
        bitmap_info = kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Host; /* XRGB */
        Amask = 0x00000000;
    } else {
        /* kCGImageAlphaFirst isn't supported */
        //bitmap_info = kCGImageAlphaFirst | kCGBitmapByteOrder32Host; /* ARGB */
        bitmap_info = kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host; /* ARGB */
        Amask = 0xFF000000;
    }
        
    Rmask = 0x00FF0000;
    Gmask = 0x0000FF00;
    Bmask = 0x000000FF;
        
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, Rmask, Gmask, Bmask, Amask);
    if (surface)
    {
        // Sets up a context to be drawn to with surface->pixels as the area to be drawn to
        bitmap_context = CGBitmapContextCreate(
                                                surface->pixels,
                                                surface->w,
                                                surface->h,
                                                bits_per_component,
                                                surface->pitch,
                                                color_space,
                                                bitmap_info
                                                );
            
        // Draws the image into the context's image_data
        CGContextDrawImage(bitmap_context, rect, image_ref);
            
        CGContextRelease(bitmap_context);
            
        // FIXME: Reverse the premultiplied alpha
        if ((bitmap_info & kCGBitmapAlphaInfoMask) == kCGImageAlphaPremultipliedFirst) {
            int i, j;
            Uint8 *p = (Uint8 *)surface->pixels;
            for (i = surface->h * surface->pitch/4; i--;) {
#if __LITTLE_ENDIAN__
                Uint8 A = p[3];
                if (A) {
                    for (j = 0; j < 3; ++j) {
                        p[j] = (p[j] * 255) / A;
                    }
                }
#else
                Uint8 A = p[0];
                if (A) {
                    for (j = 1; j < 4; ++j) {
                        p[j] = (p[j] * 255) / A;
                    }
                }
#endif /* ENDIAN */
                p += 4;
            }
        }
    }
        
    if (color_space) CGColorSpaceRelease(color_space);

    return surface;
}

@end

#endif /* __MACOSX__ */

/* vi: set ts=4 sw=4 expandtab: */
