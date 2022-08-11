//#include "StatsDisplay.h"
//
//StatsDisplay::StatsDisplay(std::ostream& output)
//	: m_output(output)
//{
//}
//
//void StatsDisplay::Update(const std::string& source, const WeatherInfo& data)
//{
//	UpdateSourceData(source, data);
//	DisplaySourceData(source);
//}
//
//void StatsDisplay::UpdateSourceData(const std::string& source, const WeatherInfo& newData)
//{
//	CreateSourceIfNotExists(source);
//	m_sources[source].UpdateEvents(newData.event);
//	m_sources[source].AddEntry(newData);
//}
//
//void StatsDisplay::CreateSourceIfNotExists(const std::string& source)
//{
//	if (!m_sources.contains(source))
//	{
//		m_sources.emplace(std::pair(source, WeatherStatistics(m_output)));
//	}
//}
//
//void StatsDisplay::DisplaySourceData(const std::string& source) const noexcept
//{
//	m_output << "Source " << source << '\n'
//			 << std::endl;
//	m_sources.at(source).Display();
//	m_output << "----------------" << std::endl;
//}