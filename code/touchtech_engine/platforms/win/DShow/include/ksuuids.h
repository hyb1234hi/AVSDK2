﻿//------------------------------------------------------------------------------
// File: ksuuids.h
//
// Desc: Contains the GUIDs for the MediaType type, subtype fields and format
//       types for DVD/MPEG2 media types.
//
// Copyright (c) 1992 - 2002, Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


//
// --- MPEG 2 definitions ---
//

// 36523B13-8EE5-11d1-8CA3-0060B057664A
OUR_GUID_ENTRY(MEDIATYPE_MPEG2_PACK,
0x36523B13, 0x8EE5, 0x11d1, 0x8C, 0xA3, 0x00, 0x60, 0xB0, 0x57, 0x66, 0x4A)

// e06d8020-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIATYPE_MPEG2_PES,
0xe06d8020, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea)


#if 0
DEFINE_GUID(MEDIATYPE_CONTROL,
0xe06d8021, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea);
#endif // #if 0


OUR_GUID_ENTRY( MEDIATYPE_MPEG2_SECTIONS,
    0x455f176c, 0x4b06, 0x47ce, 0x9a, 0xef, 0x8c, 0xae, 0xf7, 0x3d, 0xf7, 0xb5)

OUR_GUID_ENTRY(MEDIASUBTYPE_ATSC_SI,
0xb3c7397c, 0xd303, 0x414d, 0xb3, 0x3c, 0x4e, 0xd2, 0xc9, 0xd2, 0x97, 0x33)

OUR_GUID_ENTRY(MEDIASUBTYPE_DVB_SI,
0xe9dd31a3, 0x221d, 0x4adb, 0x85, 0x32, 0x9a, 0xf3, 0x9, 0xc1, 0xa4, 0x8)


// {C892E55B-252D-42b5-A316-D997E7A5D995}
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2DATA, 
0xc892e55b, 0x252d, 0x42b5, 0xa3, 0x16, 0xd9, 0x97, 0xe7, 0xa5, 0xd9, 0x95)



// e06d8026-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2_VIDEO,
0xe06d8026, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea)

// use MPEG2VIDEOINFO (defined below) with FORMAT_MPEG2_VIDEO
// e06d80e3-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(FORMAT_MPEG2_VIDEO,
0xe06d80e3, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea)

// F72A76A0-EB0A-11d0-ACE4-0000C0CC16BA       (FORMAT_VideoInfo2)
OUR_GUID_ENTRY(FORMAT_VIDEOINFO2,
0xf72a76A0L, 0xeb0a, 0x11d0, 0xac, 0xe4, 0x0, 0x0, 0xc0, 0xcc, 0x16, 0xba)

// MPEG2 Other subtypes
// e06d8022-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2_PROGRAM,
0xe06d8022, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8023-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2_TRANSPORT,
0xe06d8023, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// 138AA9A4-1EE2-4c5b-988E-19ABFDBC8A11
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2_TRANSPORT_STRIDE,
0x138aa9a4, 0x1ee2, 0x4c5b, 0x98, 0x8e, 0x19, 0xab, 0xfd, 0xbc, 0x8a, 0x11)

// e06d802b-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_MPEG2_AUDIO,
0xe06d802b, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d802c-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DOLBY_AC3,
0xe06d802c, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d802d-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DVD_SUBPICTURE,
0xe06d802d, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8032-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DVD_LPCM_AUDIO,
0xe06d8032, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8033-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DTS,
0xe06d8033, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8034-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_SDDS,
0xe06d8034, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// DVD-related mediatypes
// ED0B916A-044D-11d1-AA78-00C04FC31D60
OUR_GUID_ENTRY(MEDIATYPE_DVD_ENCRYPTED_PACK,
0xed0b916a, 0x044d, 0x11d1, 0xaa, 0x78, 0x00, 0xc0, 0x04f, 0xc3, 0x1d, 0x60)

// e06d802e-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIATYPE_DVD_NAVIGATION,
0xe06d802e, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d802f-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DVD_NAVIGATION_PCI,
0xe06d802f, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8030-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DVD_NAVIGATION_DSI,
0xe06d8030, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d8031-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(MEDIASUBTYPE_DVD_NAVIGATION_PROVIDER,
0xe06d8031, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

//
// DVD - MPEG2/AC3-related Formats
//
// e06d80e3-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(FORMAT_MPEG2Video,
0xe06d80e3, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d80e4-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(FORMAT_DolbyAC3,
0xe06d80e4, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d80e5-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(FORMAT_MPEG2Audio,
0xe06d80e5, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)

// e06d80e6-db46-11cf-b4d1-00805f6cbbea
OUR_GUID_ENTRY(FORMAT_DVD_LPCMAudio,
0xe06d80e6, 0xdb46, 0x11cf, 0xb4, 0xd1, 0x00, 0x80, 0x05f, 0x6c, 0xbb, 0xea)


//
// KS Property Set Id (to communicate with the WDM Proxy filter) -- from
// ksmedia.h of WDM DDK.
//

// BFABE720-6E1F-11D0-BCF2-444553540000
OUR_GUID_ENTRY(AM_KSPROPSETID_AC3,
0xBFABE720, 0x6E1F, 0x11D0, 0xBC, 0xF2, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00)

// ac390460-43af-11d0-bd6a-003505c103a9
OUR_GUID_ENTRY(AM_KSPROPSETID_DvdSubPic,
0xac390460, 0x43af, 0x11d0, 0xbd, 0x6a, 0x00, 0x35, 0x05, 0xc1, 0x03, 0xa9)

// 0E8A0A40L-6AEF-11D0-9ED0-00A024CA19B3
OUR_GUID_ENTRY(AM_KSPROPSETID_CopyProt,
0x0E8A0A40, 0x6AEF, 0x11D0, 0x9E, 0xD0, 0x00, 0xA0, 0x24, 0xCA, 0x19, 0xB3)

// A503C5C0-1D1D-11d1-AD80-444553540000
OUR_GUID_ENTRY(AM_KSPROPSETID_TSRateChange,
0xa503c5c0, 0x1d1d, 0x11d1, 0xad, 0x80, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0)

// 3577EB09-9582-477f-B29C-B0C452A4FF9A
OUR_GUID_ENTRY(AM_KSPROPSETID_DVD_RateChange,
0x3577eb09, 0x9582, 0x477f, 0xb2, 0x9c, 0xb0, 0xc4, 0x52, 0xa4, 0xff, 0x9a)

// ae4720ae-aa71-42d8-b82a-fffdf58b76fd
OUR_GUID_ENTRY(AM_KSPROPSETID_DvdKaraoke,
0xae4720ae, 0xaa71, 0x42d8, 0xb8, 0x2a, 0xff, 0xfd, 0xf5, 0x8b, 0x76, 0xfd)

// c830acbd-ab07-492f-8852-45b6987c2979
OUR_GUID_ENTRY(AM_KSPROPSETID_FrameStep,
0xc830acbd, 0xab07, 0x492f, 0x88, 0x52, 0x45, 0xb6, 0x98, 0x7c, 0x29, 0x79)

//
// KS categories from ks.h and ksmedia.h
//
//

// 65E8773D-8F56-11D0-A3B9-00A0C9223196
OUR_GUID_ENTRY(AM_KSCATEGORY_CAPTURE,
0x65E8773DL, 0x8F56, 0x11D0, 0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// 65E8773E-8F56-11D0-A3B9-00A0C9223196
OUR_GUID_ENTRY(AM_KSCATEGORY_RENDER,
0x65E8773EL, 0x8F56, 0x11D0, 0xA3, 0xB9, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// 1E84C900-7E70-11D0-A5D6-28DB04C10000
OUR_GUID_ENTRY(AM_KSCATEGORY_DATACOMPRESSOR,
0x1E84C900L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00)

// 6994AD04-93EF-11D0-A3CC-00A0C9223196
OUR_GUID_ENTRY(AM_KSCATEGORY_AUDIO,
0x6994AD04L, 0x93EF, 0x11D0, 0xA3, 0xCC, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// 6994AD05-93EF-11D0-A3CC-00A0C9223196
OUR_GUID_ENTRY(AM_KSCATEGORY_VIDEO,
0x6994AD05L, 0x93EF, 0x11D0, 0xA3, 0xCC, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// a799a800-a46d-11d0-a18c-00a02401dcd4
OUR_GUID_ENTRY(AM_KSCATEGORY_TVTUNER,
0xa799a800L, 0xa46d, 0x11d0, 0xa1, 0x8c, 0x00, 0xa0, 0x24, 0x01, 0xdc, 0xd4)

// a799a801-a46d-11d0-a18c-00a02401dcd4
OUR_GUID_ENTRY(AM_KSCATEGORY_CROSSBAR,
0xa799a801L, 0xa46d, 0x11d0, 0xa1, 0x8c, 0x00, 0xa0, 0x24, 0x01, 0xdc, 0xd4)

// a799a802-a46d-11d0-a18c-00a02401dcd4
OUR_GUID_ENTRY(AM_KSCATEGORY_TVAUDIO,
0xa799a802L, 0xa46d, 0x11d0, 0xa1, 0x8c, 0x00, 0xa0, 0x24, 0x01, 0xdc, 0xd4)


// 07dad660L-22f1-11d1-a9f4-00c04fbbde8f
OUR_GUID_ENTRY(AM_KSCATEGORY_VBICODEC,
0x07dad660L, 0x22f1, 0x11d1, 0xa9, 0xf4, 0x00, 0xc0, 0x4f, 0xbb, 0xde, 0x8f)


// 0A4252A0L-7E70-11D0-A5D6-28DB04C10000
OUR_GUID_ENTRY(AM_KSCATEGORY_SPLITTER,
0x0A4252A0L, 0x7E70, 0x11D0, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00)


//
// GUIDs needed to support IKsPin interface
//

// d3abc7e0l-9a61-11d0-a40d00a0c9223196
OUR_GUID_ENTRY(IID_IKsInterfaceHandler,
0xD3ABC7E0L, 0x9A61, 0x11D0, 0xA4, 0x0D, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// 5ffbaa02l-49a3-11d0-9f3600aa00a216a1
OUR_GUID_ENTRY(IID_IKsDataTypeHandler,
0x5FFBAA02L, 0x49A3, 0x11D0, 0x9F, 0x36, 0x00, 0xAA, 0x00, 0xA2, 0x16, 0xA1)

// b61178d1-a2d9-11cf-9e53-00aa00a216a1
OUR_GUID_ENTRY(IID_IKsPin,
0xb61178d1L, 0xa2d9, 0x11cf, 0x9e, 0x53, 0x00, 0xaa, 0x00, 0xa2, 0x16, 0xa1)

// 28F54685-06FD-11D2-B27A-00A0C9223196
OUR_GUID_ENTRY(IID_IKsControl,
0x28F54685L, 0x06FD, 0x11D2, 0xB2, 0x7A, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// CD5EBE6B-8B6E-11D1-8AE0-00A0C9223196
OUR_GUID_ENTRY(IID_IKsPinFactory,
0xCD5EBE6BL, 0x8B6E, 0x11D1, 0x8A, 0xE0, 0x00, 0xA0, 0xC9, 0x22, 0x31, 0x96)

// 1A8766A0-62CE-11CF-A5D6-28DB04C10000
OUR_GUID_ENTRY(AM_INTERFACESETID_Standard,
0x1A8766A0L, 0x62CE, 0x11CF, 0xA5, 0xD6, 0x28, 0xDB, 0x04, 0xC1, 0x00, 0x00)
