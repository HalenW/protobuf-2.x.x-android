// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__
#define GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__

#include <map>
#include <string>

#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;       // descriptor.h
  namespace compiler {
    namespace java {
      class Context;           // context.h
      class ClassNameResolver; // name_resolver.h
    }
  }
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace java {

// Generates code for an extension, which may be within the scope of some
// message or may be at file scope.  This is much simpler than FieldGenerator
// since extensions are just simple identifiers with interesting types.
class ExtensionGenerator {
 public:
  explicit ExtensionGenerator() {}
  virtual ~ExtensionGenerator() {}

  virtual void Generate(io::Printer* printer) = 0;
  virtual void GenerateNonNestedInitializationCode(io::Printer* printer) = 0;
  virtual void GenerateRegistrationCode(io::Printer* printer) = 0;

 protected:
  static void InitTemplateVars(const FieldDescriptor* descriptor,
                               const string& scope,
                               bool immutable,
                               ClassNameResolver* name_resolver,
                               map<string, string>* vars_pointer);

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};

class ImmutableExtensionGenerator : public ExtensionGenerator {
 public:
  explicit ImmutableExtensionGenerator(const FieldDescriptor* descriptor,
                                       Context* context);
  virtual ~ImmutableExtensionGenerator();

  virtual void Generate(io::Printer* printer);
  virtual void GenerateNonNestedInitializationCode(io::Printer* printer);
  virtual void GenerateRegistrationCode(io::Printer* printer);

 protected:
  const FieldDescriptor* descriptor_;
  Context* context_;
  ClassNameResolver* name_resolver_;
  string scope_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ImmutableExtensionGenerator);
};

}  // namespace java
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_JAVA_EXTENSION_H__
