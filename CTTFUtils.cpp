#include "CTTFUtils.hpp"
#include "include/rapidxml.hpp"

using namespace rapidxml;

bool TSVUtils::write_to_file(std::wstring in_fname, std::string out_fname) {
    // Setup libCZI objects
    auto filestream = libCZI::CreateStreamFromFile(in_fname.c_str());
    auto reader = libCZI::CreateCZIReader();
    std::shared_ptr<libCZI::ICziMetadata> metadata;
    try {
        reader->Open(filestream);
        metadata = reader->ReadMetadataSegment()
                            ->CreateMetaFromMetadataSegment();
    } catch (std::ofstream::failure e) {
        std::cout << "Failed to either open file or read metadata segment" << std::endl;
        reader->Close();
        return false;
    } 
    // Extract XML
    auto xml = metadata->GetXml(); 
    // Create DOM tree
    xml_document<> meta_xml;
    // Convert XML string into C-string and parse into DOM tree
    meta_xml.parse<0>((char *) xml.c_str());
    // Close reader; it is now unnecessary
    reader->Close();
    // Do parsing
    // Structure of XML is hard-coded for efficiency's sake
    auto image_info = meta_xml.first_node()
                            ->first_node()
                            ->first_node("Information")
                            ->first_node("Image");
    auto size_x = image_info->first_node("SizeX")->value();
    auto size_y = image_info->first_node("SizeY")->value();
    auto bit_depth = image_info->first_node("ComponentBitCount")->value();
    // Open TSV file
    std::ofstream out;
    try {
        out.open(out_fname);
    } catch (std::ofstream::failure e) {
        std::cout << "Failed to write to file \"" + out_fname + "\"." << std::endl;
        reader->Close();
        out.close();
        return false;
    }
    out << "SizeX\tSizeY\tBitDepth" << "\n";
    out << size_x << "\t" << size_y << "\t" << bit_depth << "\t" << "\n";
    out.close();
    return true;
}