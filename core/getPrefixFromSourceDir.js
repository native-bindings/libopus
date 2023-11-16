"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const assert_1 = __importDefault(require("assert"));
const path_1 = __importDefault(require("path"));
function getPrefixFromSourceDir({ sourceDir, libsDir, }) {
    assert_1.default.strict.ok(path_1.default.isAbsolute(sourceDir));
    return path_1.default.resolve(libsDir, path_1.default.basename(sourceDir));
}
exports.default = getPrefixFromSourceDir;
//# sourceMappingURL=getPrefixFromSourceDir.js.map