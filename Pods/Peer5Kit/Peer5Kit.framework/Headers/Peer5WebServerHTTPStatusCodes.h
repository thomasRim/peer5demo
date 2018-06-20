/*
 Copyright (c) 2012-2015, Pierre-Olivier Latour
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * The name of Pierre-Olivier Latour may not be used to endorse
 or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL PIERRE-OLIVIER LATOUR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

#import <Foundation/Foundation.h>

/**
 *  Convenience constants for "informational" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, Peer5WebServerInformationalHTTPStatusCode) {
  kPeer5WebServerHTTPStatusCode_Continue = 100,
  kPeer5WebServerHTTPStatusCode_SwitchingProtocols = 101,
  kPeer5WebServerHTTPStatusCode_Processing = 102
};

/**
 *  Convenience constants for "successful" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, Peer5WebServerSuccessfulHTTPStatusCode) {
  kPeer5WebServerHTTPStatusCode_OK = 200,
  kPeer5WebServerHTTPStatusCode_Created = 201,
  kPeer5WebServerHTTPStatusCode_Accepted = 202,
  kPeer5WebServerHTTPStatusCode_NonAuthoritativeInformation = 203,
  kPeer5WebServerHTTPStatusCode_NoContent = 204,
  kPeer5WebServerHTTPStatusCode_ResetContent = 205,
  kPeer5WebServerHTTPStatusCode_PartialContent = 206,
  kPeer5WebServerHTTPStatusCode_MultiStatus = 207,
  kPeer5WebServerHTTPStatusCode_AlreadyReported = 208
};

/**
 *  Convenience constants for "redirection" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, Peer5WebServerRedirectionHTTPStatusCode) {
  kPeer5WebServerHTTPStatusCode_MultipleChoices = 300,
  kPeer5WebServerHTTPStatusCode_MovedPermanently = 301,
  kPeer5WebServerHTTPStatusCode_Found = 302,
  kPeer5WebServerHTTPStatusCode_SeeOther = 303,
  kPeer5WebServerHTTPStatusCode_NotModified = 304,
  kPeer5WebServerHTTPStatusCode_UseProxy = 305,
  kPeer5WebServerHTTPStatusCode_TemporaryRedirect = 307,
  kPeer5WebServerHTTPStatusCode_PermanentRedirect = 308
};

/**
 *  Convenience constants for "client error" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, Peer5WebServerClientErrorHTTPStatusCode) {
  kPeer5WebServerHTTPStatusCode_BadRequest = 400,
  kPeer5WebServerHTTPStatusCode_Unauthorized = 401,
  kPeer5WebServerHTTPStatusCode_PaymentRequired = 402,
  kPeer5WebServerHTTPStatusCode_Forbidden = 403,
  kPeer5WebServerHTTPStatusCode_NotFound = 404,
  kPeer5WebServerHTTPStatusCode_MethodNotAllowed = 405,
  kPeer5WebServerHTTPStatusCode_NotAcceptable = 406,
  kPeer5WebServerHTTPStatusCode_ProxyAuthenticationRequired = 407,
  kPeer5WebServerHTTPStatusCode_RequestTimeout = 408,
  kPeer5WebServerHTTPStatusCode_Conflict = 409,
  kPeer5WebServerHTTPStatusCode_Gone = 410,
  kPeer5WebServerHTTPStatusCode_LengthRequired = 411,
  kPeer5WebServerHTTPStatusCode_PreconditionFailed = 412,
  kPeer5WebServerHTTPStatusCode_RequestEntityTooLarge = 413,
  kPeer5WebServerHTTPStatusCode_RequestURITooLong = 414,
  kPeer5WebServerHTTPStatusCode_UnsupportedMediaType = 415,
  kPeer5WebServerHTTPStatusCode_RequestedRangeNotSatisfiable = 416,
  kPeer5WebServerHTTPStatusCode_ExpectationFailed = 417,
  kPeer5WebServerHTTPStatusCode_UnprocessableEntity = 422,
  kPeer5WebServerHTTPStatusCode_Locked = 423,
  kPeer5WebServerHTTPStatusCode_FailedDependency = 424,
  kPeer5WebServerHTTPStatusCode_UpgradeRequired = 426,
  kPeer5WebServerHTTPStatusCode_PreconditionRequired = 428,
  kPeer5WebServerHTTPStatusCode_TooManyRequests = 429,
  kPeer5WebServerHTTPStatusCode_RequestHeaderFieldsTooLarge = 431
};

/**
 *  Convenience constants for "server error" HTTP status codes.
 */
typedef NS_ENUM(NSInteger, Peer5WebServerServerErrorHTTPStatusCode) {
  kPeer5WebServerHTTPStatusCode_InternalServerError = 500,
  kPeer5WebServerHTTPStatusCode_NotImplemented = 501,
  kPeer5WebServerHTTPStatusCode_BadGateway = 502,
  kPeer5WebServerHTTPStatusCode_ServiceUnavailable = 503,
  kPeer5WebServerHTTPStatusCode_GatewayTimeout = 504,
  kPeer5WebServerHTTPStatusCode_HTTPVersionNotSupported = 505,
  kPeer5WebServerHTTPStatusCode_InsufficientStorage = 507,
  kPeer5WebServerHTTPStatusCode_LoopDetected = 508,
  kPeer5WebServerHTTPStatusCode_NotExtended = 510,
  kPeer5WebServerHTTPStatusCode_NetworkAuthenticationRequired = 511
};
