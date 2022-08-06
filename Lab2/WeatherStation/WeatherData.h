#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class StatisticsData
{
public:
	StatisticsData(const std::string& name)
		: m_valueName(name)
	{
	}

	void UpdateStaticData(double value)
	{
		m_minValue = std::min(m_minValue, value);
		m_maxValue = std::max(m_maxValue, value);
		m_accValue += value;
		++m_countAcc;
	}

	void Display() const noexcept
	{
		std::cout << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
		std::cout << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
		std::cout << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	std::string m_valueName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_staticData.at(m_temperatureDataName).get()->UpdateStaticData(data.temperature);
		m_staticData.at(m_humidityDataName).get()->UpdateStaticData(data.humidity);
		m_staticData.at(m_pressureDataName).get()->UpdateStaticData(data.pressure);
		Display();
	}

	void Display() const noexcept
	{
		for (const auto& [_, data] : m_staticData)
		{
			data.get()->Display();
		}
	}

	const std::string m_temperatureDataName{ "Temperature" };
	const std::string m_humidityDataName{ "Humidity" };
	const std::string m_pressureDataName{ "Pressure" };

	std::map<std::string, std::shared_ptr<StatisticsData>> m_staticData{
		{ m_temperatureDataName, std::make_shared<StatisticsData>(m_temperatureDataName) },
		{ m_humidityDataName, std::make_shared<StatisticsData>(m_humidityDataName) },
		{ m_pressureDataName, std::make_shared<StatisticsData>(m_pressureDataName) }
	};
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
