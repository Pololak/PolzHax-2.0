#pragma once
#include "pch.h"
#include <fstream>
#include "utils.hpp"
#include "matplist.hpp"
//#include "pugixml.hpp"
//
//std::string createLevelExportString(gd::GJGameLevel* level) {
//	pugi::xml_document doc;
//	auto data = doc.append_child("d");
//
//	data.append_child("k").text().set("kCEK");
//	data.append_child("i").text().set(4);
//
//	data.append_child("k").text().set("k2");
//	data.append_child("s").text().set(level->m_levelName.c_str());
//
//	auto desc = base64_encode(base64_encode(level->m_levelDesc.c_str()));
//
//	data.append_child("k").text().set("k3");
//	data.append_child("s").text().set(desc.c_str());
//
//	data.append_child("k").text().set("k4");
//	data.append_child("s").text().set(level->m_levelString.c_str());
//
//	if (level->m_songID != 0) {
//		data.append_child("k").text().set("k45");
//		data.append_child("i").text().set(level->m_songID);
//	}
//	else {
//		data.append_child("k").text().set("k8");
//		data.append_child("i").text().set(level->m_audioTrack);
//	}
//
//	data.append_child("k").text().set("k13");
//	data.append_child("t");
//
//	data.append_child("k").text().set("k21");
//	data.append_child("i").text().set(2);
//
//	data.append_child("k").text().set("k50");
//	data.append_child("i").text().set(24);
//
//	std::ostringstream oss;
//	doc.save(oss, "", pugi::format_raw | pugi::format_no_declaration);
//
//	return oss.str();
//}

template <class S>
void dump_level(gd::GJGameLevel* level, S& stream) {
	const auto song_key = level->m_songID ?
		format("<k>k45</k><i>{}</i>", level->m_songID) :
		level->m_audioTrack ?
		format("<k>k8</k><i>{}</i>", level->m_audioTrack) : "";

	const auto encoded_desc = base64_encode(base64_encode(level->m_levelDesc));

	std::stringstream data;

	{
		data
		<< "<d>"
			<< "<k>kCEK</k>"
			<< "<i>4</i>"
			<< "<k>k2</k>"
			<< "<s>" << level->m_levelName << "</s>"
			<< "<k>k3</k>"
			<< "<s>" << encoded_desc
			<< "</s>"
			<< "<k>k4</k>"
			<< "<s>" << level->m_levelString
			<< "</s>"
			<< song_key
			<< "<k>k13</k>"
			<< "<t/>"
			<< "<k>k21</k>"
			<< "<i>2</i>"
			<< "<k>k50</k>"
			<< "<i>24</i>"
			<< "</d>";
	}

	stream << data.str();

	//format_to(stream, data, nullptr);

//	format_to(stream, R"(<d>
//	<k>kCEK</k>
//	<i>4</i>
//	<k>k2</k>
//	<s>{}</s>
//	<k>k3</k>
//	<s>{}</s>
//	<k>k4</k>
//	<s>{}</s>
//	{}
//	<k>k13</k><t/>
//	<k>k21</k><i>2</i>
//	<k>k50</k><i>24</i>
//</d>)", from<gd::string>(level, 0xf0).sv(), encoded_desc, from<gd::string>(level, 0x120).sv(), song_key);
//	//format_to(stream, createLevelExportString(level));
}

template <class S>
gd::GJGameLevel* import_level(S& stream) {
	auto data = matplist::parse(stream);
	auto level = gd::GameLevelManager::sharedState()->createNewLevel();
	for (const auto& [key, var] : data) {
		if (!std::holds_alternative<matplist::Value>(var)) continue;
		matplist::Value value = std::get<matplist::Value>(var);
		using namespace std::literals;
		if (key == "k2"sv) {
			from<gd::string>(level, 0xf0) = value.value;
		}
		else if (key == "k3"sv) {
			from<gd::string>(level, 0x108) = base64_decode(base64_decode(value.value));
		}
		else if (key == "k4"sv) {
			from<gd::string>(level, 0x120) = value.value;
		}
		else if (key == "k8"sv) {
			const auto text = value.value;
			from<int>(level, 0x1a4) = std::stoi(text);
		}
		else if (key == "k45"sv) {
			const auto text = value.value;
			from<int>(level, 0x1a8) = std::stoi(text);
		}
	}
	return level;
}