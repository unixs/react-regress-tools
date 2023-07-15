export interface IParserPayload {
  str: string;
}

export interface IParser {
  parser: (arg: IParserPayload) => Promise<string>,
  pthread_parser: (arg: IParserPayload) => Promise<string>
}

declare const mod: IParser;

export default mod;
