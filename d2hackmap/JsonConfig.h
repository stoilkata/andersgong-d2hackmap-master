#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <string>
#include <map>
#include <vector>

// Simple JSON value class for configuration parsing
class JsonValue {
public:
    enum Type { STRING, NUMBER, BOOLEAN, OBJECT, ARRAY, NULL_VALUE };

private:
    Type type;
    std::string stringValue;
    double numberValue;
    bool boolValue;
    std::map<std::string, JsonValue> objectValue;
    std::vector<JsonValue> arrayValue;

public:
    JsonValue() : type(NULL_VALUE), numberValue(0), boolValue(false) {}
    JsonValue(const std::string& s) : type(STRING), stringValue(s), numberValue(0), boolValue(false) {}
    JsonValue(double n) : type(NUMBER), numberValue(n), boolValue(false) {}
    JsonValue(bool b) : type(BOOLEAN), numberValue(0), boolValue(b) {}

    // Type checking
    bool isString() const { return type == STRING; }
    bool isNumber() const { return type == NUMBER; }
    bool isBool() const { return type == BOOLEAN; }
    bool isObject() const { return type == OBJECT; }
    bool isArray() const { return type == ARRAY; }
    bool isNull() const { return type == NULL_VALUE; }

    // Value getters
    std::string asString() const { return stringValue; }
    double asNumber() const { return numberValue; }
    int asInt() const { return (int)numberValue; }
    bool asBool() const { return boolValue; }

    // Object access
    JsonValue& operator[](const std::string& key) {
        if (type != OBJECT) {
            type = OBJECT;
            objectValue.clear();
        }
        return objectValue[key];
    }

    const JsonValue& operator[](const std::string& key) const {
        static JsonValue nullValue;
        if (type != OBJECT) return nullValue;
        auto it = objectValue.find(key);
        return it != objectValue.end() ? it->second : nullValue;
    }

    // Array access
    JsonValue& operator[](size_t index) {
        if (type != ARRAY) {
            type = ARRAY;
            arrayValue.clear();
        }
        if (index >= arrayValue.size()) {
            arrayValue.resize(index + 1);
        }
        return arrayValue[index];
    }

    size_t size() const {
        if (type == ARRAY) return arrayValue.size();
        if (type == OBJECT) return objectValue.size();
        return 0;
    }

    // Check if key exists in object
    bool contains(const std::string& key) const {
        return type == OBJECT && objectValue.find(key) != objectValue.end();
    }

    void setObject() { type = OBJECT; objectValue.clear(); }
    void setArray() { type = ARRAY; arrayValue.clear(); }
};

// Simple JSON parser
class JsonParser {
private:
    const char* text;
    size_t pos;
    size_t len;

    void skipWhitespace() {
        while (pos < len && (text[pos] == ' ' || text[pos] == '\t' || text[pos] == '\n' || text[pos] == '\r')) {
            pos++;
        }
    }

    std::string parseString() {
        if (text[pos] != '"') return "";
        pos++; // skip opening quote

        std::string result;
        while (pos < len && text[pos] != '"') {
            if (text[pos] == '\\' && pos + 1 < len) {
                pos++;
                switch (text[pos]) {
                    case 'n': result += '\n'; break;
                    case 't': result += '\t'; break;
                    case 'r': result += '\r'; break;
                    case '\\': result += '\\'; break;
                    case '"': result += '"'; break;
                    default: result += text[pos]; break;
                }
            } else {
                result += text[pos];
            }
            pos++;
        }

        if (pos < len) pos++; // skip closing quote
        return result;
    }

    double parseNumber() {
        size_t start = pos;
        if (text[pos] == '-') pos++;
        while (pos < len && ((text[pos] >= '0' && text[pos] <= '9') || text[pos] == '.')) {
            pos++;
        }

        std::string numberStr(text + start, pos - start);
        return atof(numberStr.c_str());
    }

    JsonValue parseValue() {
        skipWhitespace();
        if (pos >= len) return JsonValue();

        char c = text[pos];

        if (c == '"') {
            return JsonValue(parseString());
        } else if (c == '{') {
            return parseObject();
        } else if (c == '[') {
            return parseArray();
        } else if (c == 't' && pos + 4 <= len && strncmp(text + pos, "true", 4) == 0) {
            pos += 4;
            return JsonValue(true);
        } else if (c == 'f' && pos + 5 <= len && strncmp(text + pos, "false", 5) == 0) {
            pos += 5;
            return JsonValue(false);
        } else if (c == 'n' && pos + 4 <= len && strncmp(text + pos, "null", 4) == 0) {
            pos += 4;
            return JsonValue();
        } else if (c == '-' || (c >= '0' && c <= '9')) {
            return JsonValue(parseNumber());
        }

        return JsonValue();
    }

    JsonValue parseObject() {
        JsonValue obj;
        obj.setObject();

        pos++; // skip '{'
        skipWhitespace();

        if (pos < len && text[pos] == '}') {
            pos++;
            return obj;
        }

        while (pos < len) {
            skipWhitespace();

            // Parse key
            if (text[pos] != '"') break;
            std::string key = parseString();

            skipWhitespace();
            if (pos >= len || text[pos] != ':') break;
            pos++; // skip ':'

            // Parse value
            JsonValue value = parseValue();
            obj[key] = value;

            skipWhitespace();
            if (pos >= len) break;

            if (text[pos] == '}') {
                pos++;
                break;
            } else if (text[pos] == ',') {
                pos++;
            } else {
                break;
            }
        }

        return obj;
    }

    JsonValue parseArray() {
        JsonValue arr;
        arr.setArray();

        pos++; // skip '['
        skipWhitespace();

        if (pos < len && text[pos] == ']') {
            pos++;
            return arr;
        }

        size_t index = 0;
        while (pos < len) {
            JsonValue value = parseValue();
            arr[index++] = value;

            skipWhitespace();
            if (pos >= len) break;

            if (text[pos] == ']') {
                pos++;
                break;
            } else if (text[pos] == ',') {
                pos++;
                skipWhitespace();
            } else {
                break;
            }
        }

        return arr;
    }

public:
    JsonValue parse(const std::string& jsonText) {
        text = jsonText.c_str();
        pos = 0;
        len = jsonText.length();
        return parseValue();
    }
};

// Color conversion helper
DWORD ConvertColorFromJson(const JsonValue& colorValue) {
    if (colorValue.isString()) {
        std::string colorStr = colorValue.asString();

        // Handle hex colors like "#FF0000"
        if (colorStr[0] == '#' && colorStr.length() == 7) {
            return strtoul(colorStr.substr(1).c_str(), NULL, 16);
        }

        // Handle named colors
        if (colorStr == "white") return 0xFFFFFF;
        if (colorStr == "red") return 0xFF0000;
        if (colorStr == "green") return 0x00FF00;
        if (colorStr == "blue") return 0x0000FF;
        if (colorStr == "yellow") return 0xFFFF00;
        if (colorStr == "orange") return 0xFFA500;
        if (colorStr == "purple") return 0x800080;
        if (colorStr == "light_blue") return 0x87CEEB;
        if (colorStr == "light_gray") return 0xD3D3D3;
        if (colorStr == "dark_gray") return 0x696969;
        if (colorStr == "brown") return 0xA52A2A;
        if (colorStr == "dark_green") return 0x006400;
        if (colorStr == "gray") return 0x808080;

        // Handle special values
        if (colorStr == "auto") return (DWORD)-1;
        if (colorStr == "auto_hide") return (DWORD)-2;

        // Default to white if unknown
        return 0xFFFFFF;
    }

    if (colorValue.isNumber()) {
        return (DWORD)colorValue.asNumber();
    }

    return 0xFFFFFF; // Default white
}

// Virtual Key conversion helper
BYTE ConvertKeyFromJson(const std::string& keyStr) {
    if (keyStr == "L") return 'L';
    if (keyStr == "Backspace") return VK_BACK;
    if (keyStr == "NumpadMinus") return VK_SUBTRACT;
    if (keyStr == "NumpadPlus") return VK_ADD;
    if (keyStr == "Insert") return VK_INSERT;
    if (keyStr == "Minus") return VK_OEM_MINUS;
    if (keyStr == "Plus") return VK_OEM_PLUS;
    if (keyStr == "K") return 'K';
    if (keyStr == "Slash") return VK_OEM_2;
    if (keyStr == "Period") return VK_OEM_PERIOD;
    if (keyStr == "Comma") return VK_OEM_COMMA;
    if (keyStr == "9") return '9';
    if (keyStr == "0") return '0';
    if (keyStr == "F9") return VK_F9;
    if (keyStr == "F11") return VK_F11;
    if (keyStr == "NumpadDivide") return VK_DIVIDE;
    if (keyStr == "NumpadMultiply") return VK_MULTIPLY;
    if (keyStr == "8") return '8';
    if (keyStr == "Numpad1") return VK_NUMPAD1;
    if (keyStr == "Numpad2") return VK_NUMPAD2;
    if (keyStr == "Numpad3") return VK_NUMPAD3;
    if (keyStr == "Numpad4") return VK_NUMPAD4;
    if (keyStr == "Numpad6") return VK_NUMPAD6;
    if (keyStr == "Numpad7") return VK_NUMPAD7;
    if (keyStr == "Numpad8") return VK_NUMPAD8;
    if (keyStr == "Numpad9") return VK_NUMPAD9;

    // If it's a single character, return its ASCII value
    if (keyStr.length() == 1) {
        return (BYTE)toupper(keyStr[0]);
    }

    return 0; // Unknown key
}

#endif // JSONCONFIG_H