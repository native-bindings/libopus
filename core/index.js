"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.PreprocessorParser = exports.PreprocessorTokenizer = exports.Preprocessor = exports.Parser = exports.mapVariablePositions = exports.Compiler = exports.InterfaceLibrariesGenerator = exports.TokenType = exports.Tokenizer = exports.resolveVariables = exports.PkgConfigFileParser = void 0;
var PkgConfigFileParser_1 = require("./PkgConfigFileParser");
Object.defineProperty(exports, "PkgConfigFileParser", { enumerable: true, get: function () { return __importDefault(PkgConfigFileParser_1).default; } });
var resolveVariables_1 = require("./resolveVariables");
Object.defineProperty(exports, "resolveVariables", { enumerable: true, get: function () { return __importDefault(resolveVariables_1).default; } });
var Tokenizer_1 = require("./Tokenizer");
Object.defineProperty(exports, "Tokenizer", { enumerable: true, get: function () { return __importDefault(Tokenizer_1).default; } });
Object.defineProperty(exports, "TokenType", { enumerable: true, get: function () { return Tokenizer_1.TokenType; } });
var InterfaceLibrariesGenerator_1 = require("./InterfaceLibrariesGenerator");
Object.defineProperty(exports, "InterfaceLibrariesGenerator", { enumerable: true, get: function () { return __importDefault(InterfaceLibrariesGenerator_1).default; } });
var Compiler_1 = require("./Compiler");
Object.defineProperty(exports, "Compiler", { enumerable: true, get: function () { return __importDefault(Compiler_1).default; } });
var mapVariablePositions_1 = require("./mapVariablePositions");
Object.defineProperty(exports, "mapVariablePositions", { enumerable: true, get: function () { return __importDefault(mapVariablePositions_1).default; } });
var Parser_1 = require("./Parser");
Object.defineProperty(exports, "Parser", { enumerable: true, get: function () { return __importDefault(Parser_1).default; } });
var Preprocessor_1 = require("./Preprocessor");
Object.defineProperty(exports, "Preprocessor", { enumerable: true, get: function () { return __importDefault(Preprocessor_1).default; } });
var PreprocessorTokenizer_1 = require("./preprocessor/PreprocessorTokenizer");
Object.defineProperty(exports, "PreprocessorTokenizer", { enumerable: true, get: function () { return __importDefault(PreprocessorTokenizer_1).default; } });
var PreprocessorParser_1 = require("./preprocessor/PreprocessorParser");
Object.defineProperty(exports, "PreprocessorParser", { enumerable: true, get: function () { return __importDefault(PreprocessorParser_1).default; } });
//# sourceMappingURL=index.js.map