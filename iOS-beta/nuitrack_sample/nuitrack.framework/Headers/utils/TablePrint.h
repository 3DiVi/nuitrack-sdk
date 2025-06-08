#pragma once
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <vector>

namespace tdv { namespace nuitrack
{

template<size_t Columns, typename HeaderType = std::string, typename CellType = std::string>
class Table 
{
    using RowType = std::array<CellType, Columns>;
    using HeaderRowType = std::array<HeaderType, Columns>;
public:
    explicit Table(HeaderRowType&& header): _header(header)
    {
        for (size_t i = 0; i < Columns; ++i)
        {
            std::ostringstream oss;
            oss << _header[i];
            _maxColumnLengths[i] = oss.str().size();
        }
    }

    void addRow(RowType&& row)
    {
        _updateColumnLengths(row);
        _rows.push_back(std::move(row));
    }

    void printTable()
    {
        _printHeader();
        for (const auto& row : _rows)
            _printRow(row);
    }

private:
    void _updateColumnLengths(const RowType& row)
    {
        for (size_t i = 0; i < Columns; ++i)
        {
            std::ostringstream oss;
            oss << row[i];
            _maxColumnLengths[i] = std::max(_maxColumnLengths[i], oss.str().size());
        }
    }

    void _printHeader()
    {
        for (size_t i = 0; i < Columns; ++i)
        {
            std::cout << ' ' << _centered(_toString(_header[i]), _maxColumnLengths[i]);
            if (i < Columns - 1)
                std::cout << " |";
        }
        std::cout << '\n';
    }

    void _printRow(const RowType& row)
    {
        for (size_t i = 0; i < Columns; ++i)
        {
            std::cout << ' ' << std::setw(_maxColumnLengths[i]) << _toString(row[i]);
            if (i < Columns - 1)
                std::cout << " |";
        }
        std::cout << '\n';
    }

    static std::string _centered(const std::string& original, size_t targetSize)
    {
        if (original.size() >= targetSize) return original;
        const auto padding = targetSize - original.size();
        const auto paddingLeft = padding / 2;
        const auto paddingRight = padding - paddingLeft;
        return std::string(paddingLeft, ' ') + original + std::string(paddingRight, ' ');
    }

    template <typename T>
    static std::string _toString(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

private:
    const HeaderRowType _header;
    std::vector<RowType> _rows{};
    std::array<size_t, Columns> _maxColumnLengths{};
};

} // tdv
} // nuitrack