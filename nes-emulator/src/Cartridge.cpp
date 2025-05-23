#include <string>
#include <fstream>
#include "Log.h"
#include "Mapper.h"
#include "Cartridge.h"

namespace sn
{
    Byte Cartridge::getMapper()
    {
        return m_mapperNumber;
    }

    Byte Cartridge::getNameTableMirroring()
    {
        return m_nameTableMirroring;
    }

    bool Cartridge::hasExtendedRAM()
    {
        return true;
    }

    Cartridge::Cartridge() :
        m_extendedRAM(false),
        m_nameTableMirroring(0),
        m_mapperNumber(0)
    {
    }
    
    const std::vector<Byte>& Cartridge::getROM()
    {
        return m_PRG_ROM;
    }

    const std::vector<Byte>& Cartridge::getVROM()
    {
        return m_CHR_ROM;
    }

    bool Cartridge::loadFromFile(std::string path)
    {
        std::ifstream romFile(path, std::ios_base::binary | std::ios_base::in);
        if (!romFile) {
            LOG(Error) << "Could not open ROM file from path: " << path << std::endl;
            return false;
        }

        LOG(Info) << "Reading ROM from path: " << path << std::endl;
        std::vector<Byte> header(0x10);
        
        if (!romFile.read(reinterpret_cast<char*>(&header[0]), 0x10)) {
            LOG(Error) << "Reading iNES header failed." << std::endl;
            return false;
        }
        
        if (std::string{&header[0], &header[4]} != "NES\x1A") {
            LOG(Error) << "Not a valid iNES image. Magic number: "
                     << std::hex << header[0] << " " << header[1] << " " 
                     << header[2] << " " << int(header[3]) << std::endl
                     << "Valid magic number : N E S 1a" << std::endl;
            return false;
        }

        LOG(Info) << "Reading header, it dictates: \n";
        
        Byte prgBanks = header[4];
        LOG(Info) << "16KB PRG-ROM Banks: " << +prgBanks << std::endl;
        if (!prgBanks) {
            LOG(Error) << "ROM has no PRG-ROM banks. Loading ROM failed." << std::endl;
            return false;
        }

        Byte chrBanks = header[5];
        LOG(Info) << "8KB CHR-ROM Banks: " << +chrBanks << std::endl;
        
        if (header[6] & 0x8) {
            m_nameTableMirroring = NameTableMirroring::FourScreen;
            LOG(Info) << "Name Table Mirroring: " << "FourScreen" << std::endl;
        } else {
            m_nameTableMirroring = header[6] & 0x1;
            LOG(Info) << "Name Table Mirroring: " << (m_nameTableMirroring == 0 ? "Horizontal" : "Vertical") << std::endl;
        }

        m_mapperNumber = ((header[6] >> 4) & 0xf) | (header[7] & 0xf0);
        LOG(Info) << "Mapper #: " << +m_mapperNumber << std::endl;

        m_extendedRAM = header[6] & 0x2;
        LOG(Info) << "Extended (CPU) RAM: " << std::boolalpha << m_extendedRAM << std::endl;

        if (header[6] & 0x4) {
            LOG(Error) << "Trainer is not supported." << std::endl;
            return false;
        }

        if ((header[0xA] & 0x3) == 0x2 || (header[0xA] & 0x1)) {
            LOG(Error) << "PAL ROM not supported." << std::endl;
            return false;
        } else {
            LOG(Info) << "ROM is NTSC compatible.\n";
        }

        m_PRG_ROM.resize(0x4000 * prgBanks);
        if (!romFile.read(reinterpret_cast<char*>(&m_PRG_ROM[0]), 0x4000 * prgBanks)) {
            LOG(Error) << "Reading PRG-ROM from image file failed." << std::endl;
            return false;
        }

        if (chrBanks) {
            m_CHR_ROM.resize(0x2000 * chrBanks);
            if (!romFile.read(reinterpret_cast<char*>(&m_CHR_ROM[0]), 0x2000 * chrBanks)) {
                LOG(Error) << "Reading CHR-ROM from image file failed." << std::endl;
                return false;
            }
        } else {
            LOG(Info) << "Cartridge with CHR-RAM." << std::endl;
        }
        
        return true;
    }
}
