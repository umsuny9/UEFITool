/* types.cpp

Copyright (c) 2016, Nikolaj Schlej. All rights reserved.
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHWARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*/

#include "ustring.h"
#include "types.h"
#include "ffs.h"
#include "fit.h"

UString regionTypeToUString(const UINT8 type)
{
    switch (type) {
    case Subtypes::DescriptorRegion:  return UString("Descriptor");
    case Subtypes::BiosRegion:        return UString("BIOS");
    case Subtypes::MeRegion:          return UString("ME");
    case Subtypes::GbeRegion:         return UString("GbE");
    case Subtypes::PdrRegion:         return UString("PDR");
    case Subtypes::DevExp1Region:     return UString("DevExp1");
    case Subtypes::Bios2Region:       return UString("BIOS2");
    case Subtypes::MicrocodeRegion:   return UString("Microcode");
    case Subtypes::EcRegion:          return UString("EC");
    case Subtypes::DevExp2Region:     return UString("DevExp2");
    case Subtypes::IeRegion:          return UString("IE");
    case Subtypes::Tgbe1Region:       return UString("10GbE1");
    case Subtypes::Tgbe2Region:       return UString("10GbE2");
    case Subtypes::Reserved1Region:   return UString("Reserved1");
    case Subtypes::Reserved2Region:   return UString("Reserved2");
    case Subtypes::PttRegion:         return UString("PTT");
    };

    return  UString("Unknown");
}

UString itemTypeToUString(const UINT8 type)
{
    switch (type) {
    case Types::Root:           return UString("Root");
    case Types::Image:          return UString("Image");
    case Types::Capsule:        return UString("Capsule");
    case Types::Region:         return UString("Region");
    case Types::Volume:         return UString("Volume");
    case Types::Padding:        return UString("Padding");
    case Types::File:           return UString("File");
    case Types::Section:        return UString("Section");
    case Types::FreeSpace:      return UString("Free space");
    case Types::VssStore:       return UString("VSS store");
    case Types::Vss2Store:      return UString("VSS2 store");
    case Types::FtwStore:       return UString("FTW store");
    case Types::FdcStore:       return UString("FDC store");
    case Types::FsysStore:      return UString("Fsys store");
    case Types::EvsaStore:      return UString("EVSA store");
    case Types::CmdbStore:      return UString("CMDB store");
    case Types::FlashMapStore:  return UString("FlashMap store");
    case Types::NvarEntry:      return UString("NVAR entry");
    case Types::VssEntry:       return UString("VSS entry");
    case Types::FsysEntry:      return UString("Fsys entry");
    case Types::EvsaEntry:      return UString("EVSA entry");
    case Types::FlashMapEntry:  return UString("FlashMap entry");
    case Types::Microcode:      return UString("Microcode");
    case Types::SlicData:       return UString("SLIC data");
    }

    return  UString("Unknown");
}

UString itemSubtypeToUString(const UINT8 type, const UINT8 subtype)
{
    switch (type) {
    case Types::Root:
    case Types::FreeSpace:
    case Types::VssStore:
    case Types::Vss2Store:
    case Types::FdcStore:
    case Types::FsysStore:
    case Types::EvsaStore:
    case Types::FtwStore:
    case Types::FlashMapStore:
    case Types::CmdbStore:
    case Types::SlicData:                                  return UString();
    case Types::Image:
        if (subtype == Subtypes::IntelImage)               return UString("Intel");
        if (subtype == Subtypes::UefiImage)                return UString("UEFI");
        break;
    case Types::Padding:
        if (subtype == Subtypes::ZeroPadding)              return UString("Empty (0x00)");
        if (subtype == Subtypes::OnePadding)               return UString("Empty (0xFF)");
        if (subtype == Subtypes::DataPadding)              return UString("Non-empty");
        break;
    case Types::Volume: 
        if (subtype == Subtypes::UnknownVolume)            return UString("Unknown");
        if (subtype == Subtypes::Ffs2Volume)               return UString("FFSv2");
        if (subtype == Subtypes::Ffs3Volume)               return UString("FFSv3");
        if (subtype == Subtypes::NvramVolume)              return UString("NVRAM");
        break;
    case Types::Capsule: 
        if (subtype == Subtypes::AptioSignedCapsule)       return UString("Aptio signed");
        if (subtype == Subtypes::AptioUnsignedCapsule)     return UString("Aptio unsigned");
        if (subtype == Subtypes::UefiCapsule)              return UString("UEFI 2.0");
        if (subtype == Subtypes::ToshibaCapsule)           return UString("Toshiba");
        break;
    case Types::Region:                                    return regionTypeToUString(subtype);
    case Types::File:                                      return fileTypeToUString(subtype);
    case Types::Section:                                   return sectionTypeToUString(subtype);
    case Types::NvarEntry:
        if (subtype == Subtypes::InvalidNvarEntry)         return UString("Invalid");
        if (subtype == Subtypes::InvalidLinkNvarEntry)     return UString("Invalid link");
        if (subtype == Subtypes::LinkNvarEntry)            return UString("Link");
        if (subtype == Subtypes::DataNvarEntry)            return UString("Data");
        if (subtype == Subtypes::FullNvarEntry)            return UString("Full");
        break;
    case Types::VssEntry:
        if (subtype == Subtypes::InvalidVssEntry)          return UString("Invalid");
        if (subtype == Subtypes::StandardVssEntry)         return UString("Standard");
        if (subtype == Subtypes::AppleVssEntry)            return UString("Apple");
        if (subtype == Subtypes::AuthVssEntry)             return UString("Auth");
        if (subtype == Subtypes::IntelVssEntry)            return UString("Intel");
        break;
    case Types::FsysEntry:
        if (subtype == Subtypes::InvalidFsysEntry)         return UString("Invalid");
        if (subtype == Subtypes::NormalFsysEntry)          return UString("Normal");
        break;
    case Types::EvsaEntry:
        if (subtype == Subtypes::InvalidEvsaEntry)         return UString("Invalid");
        if (subtype == Subtypes::UnknownEvsaEntry)         return UString("Unknown");
        if (subtype == Subtypes::GuidEvsaEntry)            return UString("GUID");
        if (subtype == Subtypes::NameEvsaEntry)            return UString("Name");
        if (subtype == Subtypes::DataEvsaEntry)            return UString("Data");
        break;
    case Types::FlashMapEntry:
        if (subtype == Subtypes::VolumeFlashMapEntry)      return UString("Volume");
        if (subtype == Subtypes::DataFlashMapEntry)        return UString("Data");
        break;
    case Types::Microcode:
        if (subtype == Subtypes::IntelMicrocode)           return UString("Intel");
        if (subtype == Subtypes::AmdMicrocode)             return UString("AMD");
        break;
    }

    return UString("Unknown");
}

UString compressionTypeToUString(const UINT8 algorithm)
{
    switch (algorithm) {
    case COMPRESSION_ALGORITHM_NONE:         return UString("None");
    case COMPRESSION_ALGORITHM_EFI11:        return UString("EFI 1.1");
    case COMPRESSION_ALGORITHM_TIANO:        return UString("Tiano");
    case COMPRESSION_ALGORITHM_UNDECIDED:    return UString("Undecided Tiano/EFI 1.1");
    case COMPRESSION_ALGORITHM_LZMA:         return UString("LZMA");
    case COMPRESSION_ALGORITHM_IMLZMA:       return UString("Intel LZMA");
    }

    return UString("Unknown");
}

UString actionTypeToUString(const UINT8 action)
{
    switch (action) {
    case Actions::NoAction:      return UString();
    case Actions::Create:        return UString("Create");
    case Actions::Insert:        return UString("Insert");
    case Actions::Replace:       return UString("Replace");
    case Actions::Remove:        return UString("Remove");
    case Actions::Rebuild:       return UString("Rebuild");
    case Actions::Rebase:        return UString("Rebase");
    }

    return UString("Unknown");
}

UString fitEntryTypeToUString(const UINT8 type)
{
    switch (type & 0x7F) {
    case FIT_TYPE_HEADER:           return UString("FIT Header");
    case FIT_TYPE_MICROCODE:        return UString("Microcode");
    case FIT_TYPE_BIOS_AC_MODULE:   return UString("BIOS ACM");
    case FIT_TYPE_BIOS_INIT_MODULE: return UString("BIOS Init");
    case FIT_TYPE_TPM_POLICY:       return UString("TPM Policy");
    case FIT_TYPE_BIOS_POLICY_DATA: return UString("BIOS Policy Data");
    case FIT_TYPE_TXT_CONF_POLICY:  return UString("TXT Configuration Policy");
    case FIT_TYPE_AC_KEY_MANIFEST:  return UString("BootGuard Key Manifest");
    case FIT_TYPE_AC_BOOT_POLICY:   return UString("BootGuard Boot Policy");
    case FIT_TYPE_EMPTY:            return UString("Empty");
    }

    return UString("Unknown");
}